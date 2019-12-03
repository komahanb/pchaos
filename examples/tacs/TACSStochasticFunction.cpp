#include "TACSStochasticFunction.h"
#include "TACSStochasticElement.h"

namespace{

  void getDeterministicAdjoint( ParameterContainer *pc, 
                                TACSElement *delem,
                                TACSElement *selem, 
                                const TacsScalar v[],
                                TacsScalar *zq,
                                TacsScalar *uq
                                ){
    int ndvpn   = delem->getVarsPerNode();
    int nsvpn   = selem->getVarsPerNode();
    int nddof   = delem->getNumVariables();
    int nsdof   = selem->getNumVariables();
    int nsterms = pc->getNumBasisTerms();
    int nnodes  = selem->getNumNodes();
    
    memset(uq  , 0, nddof*sizeof(TacsScalar));

    // Evaluate the basis at quadrature node and form the state
    // vectors
    for (int n = 0; n < nnodes; n++){
      for (int k = 0; k < nsterms; k++){
        TacsScalar psikz = pc->basis(k,zq);
        int lptr = n*ndvpn;
        int gptr = n*nsvpn + k*ndvpn;
        for (int d = 0; d < ndvpn; d++){        
          uq[lptr+d] += v[gptr+d]*psikz;
        }
      }
    }
  } 

  void getDeterministicStates( ParameterContainer *pc, 
                               TACSElement *delem,
                               TACSElement *selem, 
                               const TacsScalar v[],
                               const TacsScalar dv[],
                               const TacsScalar ddv[], 
                               TacsScalar *zq,
                               TacsScalar *uq,
                               TacsScalar *udq,
                               TacsScalar *uddq
                               ){
    int ndvpn   = delem->getVarsPerNode();
    int nsvpn   = selem->getVarsPerNode();
    int nddof   = delem->getNumVariables();
    int nsdof   = selem->getNumVariables();
    int nsterms = pc->getNumBasisTerms();
    int nnodes  = selem->getNumNodes();

    memset(uq  , 0, nddof*sizeof(TacsScalar));
    memset(udq , 0, nddof*sizeof(TacsScalar));
    memset(uddq, 0, nddof*sizeof(TacsScalar));

    // Evaluate the basis at quadrature node and form the state
    // vectors
    for (int n = 0; n < nnodes; n++){
      for (int k = 0; k < nsterms; k++){
        TacsScalar psikz = pc->basis(k,zq);
        int lptr = n*ndvpn;
        int gptr = n*nsvpn + k*ndvpn;
        for (int d = 0; d < ndvpn; d++){        
          uq[lptr+d] += v[gptr+d]*psikz;
          udq[lptr+d] += dv[gptr+d]*psikz;
          uddq[lptr+d] += ddv[gptr+d]*psikz;
        }
      }
    }
  } 
}

TACSStochasticFunction::TACSStochasticFunction( TACSAssembler *tacs,
                                                TACSFunction *dfunc, 
                                                ParameterContainer *pc,
                                                int quantityType ) 
  : TACSFunction(tacs,
                 dfunc->getDomainType(),
                 dfunc->getStageType(),
                 0)
{
  this->dfunc = dfunc;
  this->dfunc->incref();
  this->pc = pc;
  this->quantityType = quantityType;
}

TACSStochasticFunction::~TACSStochasticFunction(){
  this->dfunc->decref();
  this->dfunc = NULL;  
  this->pc = NULL;
}

void TACSStochasticFunction::initEvaluation( EvaluationType ftype ){
  this->dfunc->initEvaluation(ftype);
}

void TACSStochasticFunction::finalEvaluation( EvaluationType evalType ){
  this->dfunc->finalEvaluation(evalType);
}

TacsScalar TACSStochasticFunction::getFunctionValue() {
  return this->dfunc->getFunctionValue();
}

void TACSStochasticFunction::elementWiseEval( EvaluationType evalType,
                                              int elemIndex,
                                              TACSElement *element,
                                              double time,
                                              TacsScalar tscale,
                                              const TacsScalar Xpts[],
                                              const TacsScalar v[],
                                              const TacsScalar dv[],
                                              const TacsScalar ddv[] ){
  TACSStochasticElement *selem = dynamic_cast<TACSStochasticElement*>(element);
  if (!selem) {
    printf("Casting to stochastic element failed; skipping elemenwiseEval");
  };
  
  TACSElement *delem = selem->getDeterministicElement();
  const int nsterms  = pc->getNumBasisTerms();
  const int nqpts    = pc->getNumQuadraturePoints();
  const int nsparams = pc->getNumParameters();
  const int ndvpn    = delem->getVarsPerNode();
  const int nsvpn    = selem->getVarsPerNode();
  const int nddof    = delem->getNumVariables();
  const int nnodes   = selem->getNumNodes();  
  
  // Space for quadrature points and weights
  TacsScalar *zq = new TacsScalar[nsparams];
  TacsScalar *yq = new TacsScalar[nsparams];
  TacsScalar wq;
  
  // Create space for deterministic states at each quadrature node in y
  TacsScalar *uq     = new TacsScalar[nddof];
  TacsScalar *udq    = new TacsScalar[nddof];
  TacsScalar *uddq   = new TacsScalar[nddof];
  
  // Stochastic Integration
  for (int q = 0; q < nqpts; q++){

    // Get the quadrature points and weights for mean
    wq = pc->quadrature(q, zq, yq);
    TacsScalar wt = pc->basis(0,zq)*wq;
    
    // Set the parameter values into the element
    selem->updateElement(delem, yq);

    // reset the states and residuals
    memset(uq   , 0, nddof*sizeof(TacsScalar));
    memset(udq  , 0, nddof*sizeof(TacsScalar));
    memset(uddq , 0, nddof*sizeof(TacsScalar));
    
    // Evaluate the basis at quadrature node and form the state
    // vectors
    for (int n = 0; n < nnodes; n++){
      for (int k = 0; k < nsterms; k++){
        TacsScalar psikz = pc->basis(k,zq);
        int lptr = n*ndvpn;
        int gptr = n*nsvpn + k*ndvpn;
        for (int d = 0; d < ndvpn; d++){        
          uq[lptr+d] += v[gptr+d]*psikz;
          udq[lptr+d] += dv[gptr+d]*psikz;
          uddq[lptr+d] += ddv[gptr+d]*psikz;
        }
      }
    }

    // Call Deterministic function with modified time weight
    TacsScalar scale = wt*tscale;
    this->dfunc->elementWiseEval(evalType, elemIndex, delem,
                                 time, scale,
                                 Xpts, uq, udq, uddq);    
  } // end yloop

  // clear allocated heap
  delete [] zq;
  delete [] yq;
  delete [] uq;
  delete [] udq;
  delete [] uddq;
}

void TACSStochasticFunction::getElementSVSens( int elemIndex, TACSElement *element,
                                               double time,
                                               TacsScalar alpha, TacsScalar beta, TacsScalar gamma,
                                               const TacsScalar Xpts[],
                                               const TacsScalar v[],
                                               const TacsScalar dv[],
                                               const TacsScalar ddv[],
                                               TacsScalar dfdu[] ){
  // zero the values
  int numVars = element->getNumVariables();
  memset(dfdu, 0, numVars*sizeof(TacsScalar));

  printf("TACSStochasticFunction::addElementSVSens \n");

  TACSStochasticElement *selem = dynamic_cast<TACSStochasticElement*>(element);
  if (!selem) {
    printf("Casting to stochastic element failed; skipping elemenwiseEval");
  };
  
  TACSElement *delem = selem->getDeterministicElement();
  const int nsterms  = pc->getNumBasisTerms();
  const int nqpts    = pc->getNumQuadraturePoints();
  const int nsparams = pc->getNumParameters();
  const int ndvpn    = delem->getVarsPerNode();
  const int nsvpn    = selem->getVarsPerNode();
  const int nddof    = delem->getNumVariables();
  const int nnodes   = selem->getNumNodes();  

  // j-th project
  TacsScalar *dfduj  = new TacsScalar[nddof];  
  
  // Space for quadrature points and weights
  TacsScalar *zq = new TacsScalar[nsparams];
  TacsScalar *yq = new TacsScalar[nsparams];
  TacsScalar wq;
  
  // Create space for deterministic states at each quadrature node in y
  TacsScalar *uq     = new TacsScalar[nddof];
  TacsScalar *udq    = new TacsScalar[nddof];
  TacsScalar *uddq   = new TacsScalar[nddof];

  for (int j = 0; j < nsterms; j++){

    memset(dfduj, 0, nddof*sizeof(TacsScalar));
    
    // Stochastic Integration
    for (int q = 0; q < nqpts; q++){

      // Get the quadrature points and weights for mean
      wq = pc->quadrature(q, zq, yq);
      TacsScalar wt = pc->basis(j,zq)*wq;
    
      // Set the parameter values into the element
      selem->updateElement(delem, yq);

      // reset the states and residuals
      memset(uq   , 0, nddof*sizeof(TacsScalar));
      memset(udq  , 0, nddof*sizeof(TacsScalar));
      memset(uddq , 0, nddof*sizeof(TacsScalar));
    
      // Evaluate the basis at quadrature node and form the state
      // vectors
      for (int n = 0; n < nnodes; n++){
        for (int k = 0; k < nsterms; k++){
          TacsScalar psikz = pc->basis(k,zq);
          int lptr = n*ndvpn;
          int gptr = n*nsvpn + k*ndvpn;
          for (int d = 0; d < ndvpn; d++){        
            uq[lptr+d] += v[gptr+d]*psikz;
            udq[lptr+d] += dv[gptr+d]*psikz;
            uddq[lptr+d] += ddv[gptr+d]*psikz;
          }
        }
      }

      // Call Deterministic function with modified time weight
      // this->dfunc->elementWiseEval(evalType, elemIndex, delem,
      //                              time, scale,
      //                              Xpts, uq, udq, uddq);
  
      // Call the underlying element and get the state variable sensitivities
      double pt[3] = {0.0,0.0,0.0};
      int N = 1;
      TacsScalar _dfdq = 1.0;      
      delem->addPointQuantitySVSens(elemIndex,
                                    this->quantityType,
                                    time, wt*alpha, wt*beta, wt*gamma,
                                    N, pt,
                                    Xpts, uq, udq, uddq, &_dfdq, 
                                    dfduj); // store into tmp
    } // end yloop
    
    // Store j-th projected sv sens into stochastic array
    for (int n = 0; n < nnodes; n++){
      int lptr = n*ndvpn;
      int gptr = n*nsvpn + j*ndvpn;
      for (int d = 0; d < ndvpn; d++){        
        dfdu[gptr+d] = dfduj[lptr+d];
      }
    }

  } // end nsterms

  // clear allocated heap
  delete [] dfduj;
  delete [] zq;
  delete [] yq;
  delete [] uq;
  delete [] udq;
  delete [] uddq;
}

void TACSStochasticFunction::addElementDVSens( int elemIndex, TACSElement *element,
                                               double time, TacsScalar scale,
                                               const TacsScalar Xpts[], const TacsScalar v[],
                                               const TacsScalar dv[], const TacsScalar ddv[],
                                               int dvLen, TacsScalar dfdx[] ){
  printf("TACSStochasticFunction::addElementDVSens \n");
  TACSStochasticElement *selem = dynamic_cast<TACSStochasticElement*>(element);
  if (!selem) {
    printf("Casting to stochastic element failed; skipping elemenwiseEval");
  };
  TACSElement *delem = selem->getDeterministicElement();

  const int nsterms  = pc->getNumBasisTerms();
  const int nqpts    = pc->getNumQuadraturePoints();
  const int nsparams = pc->getNumParameters();
  const int ndvpn    = delem->getVarsPerNode();
  const int nsvpn    = selem->getVarsPerNode();
  const int nddof    = delem->getNumVariables();
  const int nnodes   = selem->getNumNodes();  

  // j-th projection of dfdx array
  TacsScalar *dfdxj  = new TacsScalar[dvLen];
  
  // Space for quadrature points and weights
  TacsScalar *zq = new TacsScalar[nsparams];
  TacsScalar *yq = new TacsScalar[nsparams];
  TacsScalar wq;
  
  // Create space for deterministic states at each quadrature node in y
  TacsScalar *uq     = new TacsScalar[nddof];
  TacsScalar *udq    = new TacsScalar[nddof];
  TacsScalar *uddq   = new TacsScalar[nddof];

  for (int j = 0; j < 1; j++){ // nsterms

    memset(dfdxj, 0, dvLen*sizeof(TacsScalar));
    
    // Stochastic Integration
    for (int q = 0; q < nqpts; q++){

      // Get the quadrature points and weights for mean
      wq = pc->quadrature(q, zq, yq);
      TacsScalar wt = pc->basis(j,zq)*wq;
    
      // Set the parameter values into the element
      selem->updateElement(delem, yq);

      // form deterministic states      
      getDeterministicStates(pc, delem, selem, v, dv, ddv, zq, uq, udq, uddq);

      // Call the underlying element and get the state variable sensitivities
      double pt[3] = {0.0,0.0,0.0};
      int N = 1;
      TacsScalar _dfdq = 1.0; 
      delem->addPointQuantityDVSens( elemIndex, 
                                     this->quantityType,
                                     time, wt*scale,
                                     N, pt,
                                     Xpts, uq, udq, uddq, &_dfdq, 
                                     dvLen, dfdxj ); 
    } // end yloop

    // need to be careful with nodewise placement of dvs
    for (int n = 0; n < dvLen; n++){
      //      printf("term %d dfdx[%d] = %.17e %.17e \n", j, n, dfdx[n], dfdxj[n]);
      dfdx[n] += dfdxj[n];
    }
    
    // // check this
    // // Store j-th projected sv sens into stochastic array
    // for (int n = 0; n < nnodes; n++){
    //   int lptr = n*ndvpn;
    //   int gptr = n*nsvpn + j*ndvpn;
    //   for (int d = 0; d < ndvpn; d++){        
    //     dfdx[gptr+d] = dfdxj[lptr+d];
    //   }
    // }

  } // end nsterms

  // clear allocated heap
  delete [] zq;
  delete [] yq;
  delete [] uq;
  delete [] udq;
  delete [] uddq;
  delete [] dfdxj;
}
