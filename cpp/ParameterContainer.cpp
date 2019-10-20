#include"ParameterContainer.h"
#include"ParameterFactory.h"

ParameterContainer::ParameterContainer(){
  this->tnum_parameters = 0;
}
ParameterContainer::~ParameterContainer(){

  if(param_max_degree){delete [] param_max_degree;};

  for (int k = 0; k < this->tnum_basis_terms; k++){
    delete [] this->dindex[k];
  };
  delete [] this->dindex;

  // Deallocate Z, Y, W  
}

/*
  Add the parameter into  collection
*/
void ParameterContainer::addParameter(AbstractParameter *param){
  if (this->tnum_parameters > 4){
    printf("Warning: Parameter container is full\n");
  }
  this->pmap.insert(pair<int, AbstractParameter*>(param->getParameterID(), param));
  this->tnum_parameters++;
}

int ParameterContainer::getNumBasisTerms(){
  return this->tnum_basis_terms;
}

int ParameterContainer::getNumParameters(){
  return this->tnum_parameters;
}

int ParameterContainer::getNumQuadraturePoints(){
  return this->tnum_quadrature_points;
}

void  ParameterContainer::initializeBasis(const int *pmax){
  int nvars = this->getNumParameters();
  
  // Copy over the max degrees
  param_max_degree = new int[nvars];
  for (int k = 0; k < nvars; k++){
    param_max_degree[k] = pmax[k];
  }

  // Number of terms from tensor product
  int nterms = 1;
  for (int i = 0; i < nvars; i++){
    nterms *= 1 + pmax[i];
  }

  // Allocate space for storing degree set
  this->dindex = new int*[nterms];
  for (int k = 0; k < nterms; k++){
    this->dindex[k] = new int[nvars];
  }
  
  // Generate and store a set of indices
  this->bhelper->basisDegrees(nvars, pmax, 
                              &this->tnum_basis_terms, 
                              this->dindex);

  if (this->tnum_basis_terms != nterms){
    printf("Error initializing basis\n");
  };
}

void ParameterContainer::initializeQuadrature(const int *nqpts){  
  const int nvars = getNumParameters();
  int totquadpts = 1;
  for (int i = 0; i < nvars; i++){
    totquadpts *= nqpts[i];
  }
  this->tnum_quadrature_points = totquadpts;
  
  // Get the univariate quadrature points from parameters
  double **y = new double*[nvars];
  double **z = new double*[nvars];
  double **w = new double*[nvars];
  for (int i = 0; i < nvars; i++){
    z[i] = new double[nqpts[i]];
    y[i] = new double[nqpts[i]];
    w[i] = new double[nqpts[i]];    
  }
  map<int,AbstractParameter*>::iterator it;
  for (it = this->pmap.begin(); it != this->pmap.end(); it++){
    int pid = it->first;
    it->second->quadrature(nqpts[pid], z[pid], y[pid], w[pid]);
  }

  // Allocate space for return variables  
  // for (int i = 0; i < nvars; i++){
  //   if (Z[i]){ delete Z[i]; };
  //   if (Y[i]){ delete Y[i]; };
  // }
  // if (Z){ delete [] Z; };
  // if (Y){ delete [] Y; };
  // if (W){ delete [] W; };  

  Z = new double*[nvars];
  Y = new double*[nvars];
  W = new double[totquadpts];  
  for (int i = 0; i < nvars; i++){
    Z[i] = new double[totquadpts];
    Y[i] = new double[totquadpts];    
  }

  // Find tensor product of 1d rules
  qhelper->tensorProduct(nvars, nqpts, z, y, w, Z, Y, W);
  
  // Deallocate space
  for (int i = 0; i < nvars; i++){
    delete z[i];
    delete y[i];
    delete w[i];
  }
  delete [] y;
  delete [] z;
  delete [] w;
}

/*
 */
void ParameterContainer::quadrature(int q,
                                    double *zq, double *yq, double *wq){
  const int nvars = getNumParameters(); 
  wq[0] = this->W[q];
  for (int i = 0; i < nvars; i++){
    zq[i] = this->Z[i][q];
    yq[i] = this->Y[i][q];
  }
}

/*
  Evaluate the k-the basis function at point "z"
*/
double ParameterContainer::basis(int k, double *z){
  double psi = 1.0;
  map<int,AbstractParameter*>::iterator it;
  for (it = this->pmap.begin(); it != this->pmap.end(); it++){
    int pid = it->first;
    //printf("%d %d \n", pid, this->dindex[k][pid]);
    psi *= it->second->basis(z[pid], this->dindex[k][pid]);
  }
  return psi;
}

int main( int argc, char *argv[] ){
  // Create random parameters
  ParameterFactory *factory = new ParameterFactory();
  AbstractParameter *p1 = factory->createNormalParameter(-4.0, 0.5);
  AbstractParameter *p2 = factory->createUniformParameter(-5.0, 4.0);  
  AbstractParameter *p3 = factory->createExponentialParameter(6.0, 1.0);
  AbstractParameter *p4 = factory->createExponentialParameter(6.0, 1.0);
  AbstractParameter *p5 = factory->createNormalParameter(-4.0, 0.5);
   
  // Create container and add random paramters
  ParameterContainer *pc = new ParameterContainer();
  pc->addParameter(p1);
  pc->addParameter(p2);
  pc->addParameter(p3);
  pc->addParameter(p4);
  pc->addParameter(p5);

  // Set max degrees of expansion and get corresponding number of
  // quadrature points
  const int nvars = pc->getNumParameters();
  // int *pmax = new int[nvars];
  // int *nqpts = new int[nvars];
  // for (int i = 0; i < nvars; i++){
  //   pmax[i] = i+2;
  //   nqpts[i] = pmax[i]+1;
  // }


  int pmax[] = {3,3,4,4,2};
  int nqpts[] = {4,4,5,5,3};
  
  printf("max orders        = ");
  for (int i = 0; i < nvars; i++){
    printf("%d ", pmax[i]);
  }
  printf("\nquadrature points = ");
  for (int i = 0; i < nvars; i++){
    printf("%d ", nqpts[i]);
  }
  printf("\n");

  // Initialize basis
  pc->initializeBasis(pmax);
  int nbasis = pc->getNumBasisTerms();

  // Initialize quadrature
  pc->initializeQuadrature(nqpts);  
  int nqpoints = pc->getNumQuadraturePoints();

  printf("%d %d \n", nqpoints, nbasis);
  
  // Space for quadrature points and weights
  double *zq = new double[nvars];
  double *yq = new double[nvars];
  double wq;

  // for (int q = 0; q < nqpoints; q++){
  //   pc->quadrature(q, zq, yq, &wq);
  // }

  for (int k = 0; k < nbasis; k++){
    for (int q = 0; q < nqpoints; q++){
      pc->quadrature(q, zq, yq, &wq);
      pc->basis(k,zq);
      // printf("%6d %6d %13.6f\n", k, q, pc->basis(k,zq));
    }
  }
    
  return 1;
}