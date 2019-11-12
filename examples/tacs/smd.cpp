#include "TACSAssembler.h"
#include "TACSIntegrator.h"
#include "ParameterContainer.h"
#include "ParameterFactory.h"
#include "TACSStochasticElement.h"
#include "TACSCreator.h"
#include "smd.h"

#include "TACSFunction.h"
#include "TACSStochasticFunction.h"
#include "TACSEnergy.h"

void updateSMD( TACSElement *elem, TacsScalar *vals ){
  SMD *smd = dynamic_cast<SMD*>(elem);
  if (smd != NULL) {
    smd->m = vals[0];
    smd->c = vals[1];
    smd->k = vals[2];
    //    printf("%e %e %e \n", smd->m, smd->c, smd->k);
  } else {
    printf("Element mismatch while updating...");
  }
}

SMD::SMD(double m, double c, double k){
  this->m = m;
  this->c = c;
  this->k = k;  
}

void SMD::getInitConditions( int elemIndex, const TacsScalar X[],
                             TacsScalar v[], TacsScalar dv[], TacsScalar ddv[] ){
  int num_vars = getNumNodes()*getVarsPerNode();
  memset(v, 0, num_vars*sizeof(TacsScalar));
  memset(dv, 0, num_vars*sizeof(TacsScalar));
  memset(ddv, 0, num_vars*sizeof(TacsScalar));

  // set init conditions
  v[0] = 1.0;
  dv[0] = 0.0;
}

void SMD::addResidual( int elemIndex, double time,
                         const TacsScalar X[], const TacsScalar v[],
                         const TacsScalar dv[], const TacsScalar ddv[],
                         TacsScalar res[] ){
  res[0] += m*ddv[0] + c*dv[0] + k*v[0];
}

void SMD::addJacobian( int elemIndex, double time,
                       TacsScalar alpha, TacsScalar beta, TacsScalar gamma,
                       const TacsScalar X[], const TacsScalar v[],
                       const TacsScalar dv[], const TacsScalar ddv[],
                       TacsScalar res[], TacsScalar mat[] ){
  addResidual(elemIndex, time, X, v, dv, ddv, res);
  mat[0] += gamma*m + beta*c + alpha*k;
}

int SMD::evalPointQuantity( int elemIndex, int quantityType,
                            double time,
                            int n, double pt[],
                            const TacsScalar Xpts[],
                            const TacsScalar vars[],
                            const TacsScalar dvars[],
                            const TacsScalar ddvars[],
                            TacsScalar *quantity ){
  // kinetic energy
  quantity[0] = 0.5*k*vars[0]*vars[0];
  return 1;
}

int main( int argc, char *argv[] ){  
  // Initialize MPI
  MPI_Init(&argc, &argv);
  MPI_Comm comm = MPI_COMM_WORLD;
  int rank; 
  MPI_Comm_rank(comm, &rank); 

  //-----------------------------------------------------------------//
  // Choose solution mode (deterministic = 0 or 1)
  //-----------------------------------------------------------------//
  
  int deterministic = 0;

  //-----------------------------------------------------------------//
  // Define random parameters with distribution functions
  //-----------------------------------------------------------------//
  
  ParameterFactory *factory = new ParameterFactory();
  AbstractParameter *m = factory->createExponentialParameter(1.0, 0.25, 1);
  AbstractParameter *c = factory->createUniformParameter(0.2, 0.5, 1);
  AbstractParameter *k = factory->createNormalParameter(5.0, 0.1, 1);
 
  ParameterContainer *pc = new ParameterContainer();
  pc->addParameter(m);
  pc->addParameter(c);
  pc->addParameter(k);

  pc->initialize();
  int nsterms = pc->getNumBasisTerms();
  printf("nsterms = %d \n", nsterms);
  
  //-----------------------------------------------------------------//
  // Create deterministic and stochastic elements
  //-----------------------------------------------------------------//
 
  TACSElement *smd = new SMD(2.5, 0.2, 5.0); 
  smd->incref();

  TACSStochasticElement *ssmd = new TACSStochasticElement(smd, pc, updateSMD);
  ssmd->incref();

  int nelems = 1;
  int nnodes = 1;  
  int vars_per_node = 1;
  if (!deterministic){
    vars_per_node *= nsterms;
  }

  // Array of elements
  TACSElement **elems = new TACSElement*[nelems];
  if (deterministic){
    elems[0] = smd;
  } else{
    elems[0] = ssmd;
  }

  // Node points array
  TacsScalar *X = new TacsScalar[3*nnodes];
  memset(X, 0, nnodes*sizeof(TacsScalar));

  // Connectivity array
  int *conn = new int[1];
  conn[0] = 0;

  // Connectivity pointer array
  int *ptr = new int[2];
  ptr[0] = 0;
  ptr[1] = 1;

  // Element Ids array
  int *eids = new int[nelems];
  for (int i = 0; i < nelems; i++){
    eids[i] = i;
  }
  
  // Creator object for TACS
  TACSCreator *creator = new TACSCreator(comm, vars_per_node);
  creator->incref();
  if (rank == 0){    
    creator->setGlobalConnectivity(nnodes, nelems, ptr, conn, eids);
    creator->setNodes(X);
  }
  creator->setElements(nelems, elems);

  TACSAssembler *assembler = creator->createTACS();
  assembler->incref();
  creator->decref();

  delete [] X;
  delete [] ptr;
  delete [] eids;
  delete [] conn;
  delete [] elems;
  
  // Create deterministic function to evaluate
  TACSFunction *ke = new TACSEnergy(assembler);
  TACSFunction *ske = new TACSStochasticFunction(assembler, ke, pc);

  // Create an array of functions for TACS to evaluate
  const int num_funcs = 1;
  TACSFunction **funcs = new TACSFunction*[num_funcs];
  if (deterministic){
    funcs[0] = ke;
  } else {
    funcs[0] = ske;
  }
  
  // Create the integrator class
  TACSIntegrator *bdf = new TACSBDFIntegrator(assembler, 0.0, 10.0, 1000, 2);
  bdf->incref();
  bdf->setAbsTol(1e-7);
  bdf->setPrintLevel(0);
  bdf->setFunctions(num_funcs, funcs);
  bdf->integrate();
  bdf->writeRawSolution("smd.dat", 1);

  TacsScalar *ftmp = new TacsScalar[ num_funcs ];
  ftmp[0] = 0.0;
  bdf->evalFunctions(ftmp);
  printf("func val is %e\n", ftmp[0]);
    
  // write solution and test
  bdf->decref();
  assembler->decref();  
  MPI_Finalize();
  return 0;
}
