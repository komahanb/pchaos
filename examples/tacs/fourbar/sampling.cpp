#include "TACSAssembler.h"
#include "TACSIntegrator.h"
#include "TACSRigidBody.h"
#include "TACSKinematicConstraints.h"
#include "SquareSection.h"
#include "MITC3.h"
#include "TACSKSFailure.h"
#include "TACSStructuralMass.h"
#include "TACSConstitutiveVerification.h"
#include "TACSElementVerification.h"
#include "ParameterContainer.h"
#include "ParameterFactory.h"

/*
  Create and return the TACSAssembler object for the four bar
  mechanism as described by Bachau

  B ------------------- C
  |                     |
  |                     |
  |                     |
  A                     D

  Length between A and B = 0.12 m
  Length between B and C = 0.24 m
  Length between C and D = 0.12 m

  A, B and D are revolute joints in the plane perpendicular to the
  plane of the mechanism

  C is a revolute joint in a plane +5 degrees along the DC axis of the
  beam

  Beam properties:

  Young's modulus 207 GPa, nu = 0.3

  Bars 1 and 2 are square and of dimension 16 x 16 mm
  Bar 3 is square and of dimension 8 x 8 mm
*/
TACSAssembler *four_bar_mechanism( int nA, int nB, int nC, TacsScalar _theta ){
  //  printf("speed = %e \n", _omega);
  // Set the gravity vector
  TACSGibbsVector *gravity = new TACSGibbsVector(0.0, 0.0, -9.81);

  // Set the points b, c and d
  TACSGibbsVector *ptB = new TACSGibbsVector(0.0, 0.12, 0.0);
  TACSGibbsVector *ptC = new TACSGibbsVector(0.24, 0.12, 0.0);
  TACSGibbsVector *ptD = new TACSGibbsVector(0.24, 0.0, 0.0);

  // Create the revolute direction for B and D
  TACSGibbsVector *revDirA = new TACSGibbsVector(0.0, 0.0, 1.0);
  TACSGibbsVector *revDirB = new TACSGibbsVector(0.0, 0.0, 1.0);
  TACSGibbsVector *revDirD = new TACSGibbsVector(0.0, 0.0, 1.0);

  // Create the revolute direction for C
  TacsScalar theta = (_theta*M_PI/180.0);
  TACSGibbsVector *revDirC = new TACSGibbsVector(sin(theta), 0.0, cos(theta));

  // Create the revolute constraints
  TacsScalar omega = -0.6; // rad/seconds
  int fixed_point = 1;
  int not_fixed = 0;

  TACSRevoluteDriver *revDriverA =
    new TACSRevoluteDriver(revDirA, omega);
  TACSRevoluteConstraint *revB =
    new TACSRevoluteConstraint(not_fixed, ptB, revDirB);
  TACSRevoluteConstraint *revC =
    new TACSRevoluteConstraint(not_fixed, ptC, revDirC);
  TACSRevoluteConstraint *revD =
    new TACSRevoluteConstraint(fixed_point, ptD, revDirD);

  // Set the reference axes for each beam
  TacsScalar axis_A[] = {-1.0, 0.0, 0.0};
  TacsScalar axis_B[] = {0.0, 1.0, 0.0};
  TacsScalar axis_C[] = {1.0, 0.0, 0.0};

  // Set the material properties
  TacsScalar density = 7800.0;
  TacsScalar E = 207e9;
  TacsScalar nu = 0.3;
  TacsScalar G = 0.5*E/(1.0 + nu);

  TacsScalar wA = 0.016;
  TacsScalar wB = 0.008;
  int wANum = 0, wBNum = 1;

  TACSTimoshenkoConstitutive *stiffA =
    new SquareSection(density, E, G, wA, wANum, axis_A);

  TACSTimoshenkoConstitutive *stiffB =
    new SquareSection(density, E, G, wA, wANum, axis_B);

  TACSTimoshenkoConstitutive *stiffC =
    new SquareSection(density, E, G, wB, wBNum, axis_C);

  // Set up the connectivity
  MITC3 *beamA = new MITC3(stiffA, gravity);
  MITC3 *beamB = new MITC3(stiffB, gravity);
  MITC3 *beamC = new MITC3(stiffC, gravity);

  // Set the number of nodes in the mesh
  int nnodes = (2*nA+1) + (2*nB+1) + (2*nC+1) + 4;

  // Set the number of elements
  int nelems = nA + nB + nC + 4;

  // Create the connectivities
  TacsScalar *X = new TacsScalar[ 3*nnodes ];
  memset(X, 0, 3*nnodes*sizeof(TacsScalar));

  int *ptr = new int[ nelems+1 ];
  int *conn = new int[ 3*nelems ];
  TACSElement **elems = new TACSElement*[ nelems ];

  // Set the nodes numbers and locations
  int *nodesA = new int[ 2*nA+1 ];
  int *nodesB = new int[ 2*nB+1 ];
  int *nodesC = new int[ 2*nC+1 ];
  int n = 0;
  for ( int i = 0; i < 2*nA+1; i++, n++ ){
    nodesA[i] = n;
    X[3*n+1] = 0.12*i/(2*nA);
  }
  for ( int i = 0; i < 2*nB+1; i++, n++ ){
    nodesB[i] = n;
    X[3*n] = 0.24*i/(2*nB);
    X[3*n+1] = 0.12;
  }
  for ( int i = 0; i < 2*nC+1; i++, n++ ){
    nodesC[i] = n;
    X[3*n] = 0.24;
    X[3*n+1] = 0.12*(1.0 - 1.0*i/(2*nC));
  }

  // Set the connectivity for the beams
  int elem = 0;
  ptr[0] = 0;
  for ( int i = 0; i < nA; i++ ){
    conn[ptr[elem]] = nodesA[2*i];
    conn[ptr[elem]+1] = nodesA[2*i+1];
    conn[ptr[elem]+2] = nodesA[2*i+2];
    elems[elem] = beamA;
    ptr[elem+1] = ptr[elem] + 3;
    elem++;
  }

  for ( int i = 0; i < nB; i++ ){
    conn[ptr[elem]] = nodesB[2*i];
    conn[ptr[elem]+1] = nodesB[2*i+1];
    conn[ptr[elem]+2] = nodesB[2*i+2];
    elems[elem] = beamB;
    ptr[elem+1] = ptr[elem] + 3;
    elem++;
  }

  for ( int i = 0; i < nC; i++ ){
    conn[ptr[elem]] = nodesC[2*i];
    conn[ptr[elem]+1] = nodesC[2*i+1];
    conn[ptr[elem]+2] = nodesC[2*i+2];
    elems[elem] = beamC;
    ptr[elem+1] = ptr[elem] + 3;
    elem++;
  }

  // Add the connectivities for the constraints
  conn[ptr[elem]] = nodesA[0];
  conn[ptr[elem]+1] = nnodes-4;
  elems[elem] = revDriverA;
  ptr[elem+1] = ptr[elem] + 2;
  elem++;

  conn[ptr[elem]] = nodesA[2*nA];
  conn[ptr[elem]+1] = nodesB[0];
  conn[ptr[elem]+2] = nnodes-3;
  elems[elem] = revB;
  ptr[elem+1] = ptr[elem] + 3;
  elem++;

  conn[ptr[elem]] = nodesC[0];
  conn[ptr[elem]+1] = nodesB[2*nB];
  conn[ptr[elem]+2] = nnodes-2;
  elems[elem] = revC;
  ptr[elem+1] = ptr[elem] + 3;
  elem++;

  conn[ptr[elem]] = nodesC[2*nC];
  conn[ptr[elem]+1] = nnodes-1;
  elems[elem] = revD;
  ptr[elem+1] = ptr[elem] + 2;
  elem++;

  delete [] nodesA;
  delete [] nodesB;
  delete [] nodesC;

  // Create the TACSAssembler object
  TACSAssembler *assembler = new TACSAssembler(MPI_COMM_WORLD, 8, nnodes, nelems);

  assembler->setElementConnectivity(ptr, conn);
  delete [] conn;
  delete [] ptr;

  assembler->setElements(elems);
  delete [] elems;

  assembler->initialize();

  // Set the node locations
  TACSBVec *Xvec = assembler->createNodeVec();
  Xvec->incref();
  TacsScalar *Xarray;
  Xvec->getArray(&Xarray);
  memcpy(Xarray, X, 3*nnodes*sizeof(TacsScalar));
  assembler->setNodes(Xvec);
  Xvec->decref();
  delete [] X;

  return assembler;
}

int main( int argc, char *argv[] ){
  // Initialize MPI
  MPI_Init(&argc, &argv);

  // The number of total steps (100 per second)
  const int num_steps = 1200;  
  const int num_bars = 3;
  int pnqpts[1] = {15};
  ParameterFactory *factory = new ParameterFactory();
  //AbstractParameter *pspeed = factory->createNormalParameter(-0.6, 0.06, 0);  
  AbstractParameter *ptheta = factory->createNormalParameter(5.0, 2.5, 0);  

  ParameterContainer *pc = new ParameterContainer();
  //  pc->addParameter(pspeed);
  pc->addParameter(ptheta);
  pc->initializeQuadrature(pnqpts);

  const int nqpoints = pc->getNumQuadraturePoints();
  const int nvars = pc->getNumParameters();

  TacsScalar ***data = new TacsScalar**[nqpoints];
  for (int i = 0; i < nqpoints; i++){
    data[i] = new TacsScalar*[num_bars];
    for (int j = 0; j < num_bars; j++){
      data[i][j] = new TacsScalar[num_steps];
    }
  }

  TacsScalar *failmeanbar1 = new TacsScalar[num_steps];
  memset(failmeanbar1, 0, num_steps*sizeof(TacsScalar));

  TacsScalar *fail2meanbar1 = new TacsScalar[num_steps];
  memset(fail2meanbar1, 0, num_steps*sizeof(TacsScalar));

  TacsScalar *failvarbar1 = new TacsScalar[num_steps];
  memset(failvarbar1, 0, num_steps*sizeof(TacsScalar));

  TacsScalar *zq = new TacsScalar[nvars];
  TacsScalar *yq = new TacsScalar[nvars];
  TacsScalar wq;

  for (int iq = 0; iq < nqpoints; iq++){

    wq = pc->quadrature(iq, zq, yq);

    // Create the finite-element model
    int nA = 4, nB = 8, nC = 4;
    TACSAssembler *assembler = four_bar_mechanism(nA, nB, nC, yq[0]);
    assembler->incref();

    // Set the final time
    double tf = 12.0;

    // Create the integrator class
    TACSIntegrator *integrator =
      new TACSBDFIntegrator(assembler, 0.0, tf, num_steps, 2);
    integrator->incref();

    // Set the integrator options
    integrator->setUseSchurMat(1, TACSAssembler::TACS_AMD_ORDER);
    integrator->setAbsTol(1e-7);
    integrator->setRelTol(1e-12);
    integrator->setOutputFrequency(0);

    // Integrate the equations of motion forward in time
    integrator->integrate();

    // Create the continuous KS function
    double ksRho = 100.0;
    TACSKSFailure *ksfunc = new TACSKSFailure(assembler, ksRho);
    TACSStructuralMass *fmass = new TACSStructuralMass(assembler);

    // Set the functions
    TACSFunction *funcs = fmass; // ksfunc
    integrator->setFunctions(1, &funcs);

    TacsScalar fval;
    integrator->evalFunctions(&fval);
    printf("Function value: %15.10e\n", TacsRealPart(fval));

    // Evaluate the adjoint
    integrator->integrateAdjoint();

    // Get the gradient
    TACSBVec *dfdx;
    integrator->getGradient(0, &dfdx);

#ifdef TACS_USE_COMPLEX
    //  integrator->checkGradients(1e-30);
#else
    //  integrator->checkGradients(1e-6);
#endif // TACS_USE_COMPLEX

    // Set the output options/locations
    int elem[3];
    elem[0] = nA/2;
    elem[1] = nA + nB/2;
    elem[2] = nA + nB + nC/2;
    double param[][1] = {{-1.0}, {-1.0}, {0.0}};

    // Extra the data to a file
    for ( int pt = 0; pt < 3; pt++ ){
      char filename[128];
      sprintf(filename, "mid_beam_%d_%d.dat", pt+1, iq);
      FILE *fp = fopen(filename, "w");

      fprintf(fp, "Variables = t, u0, v0, w0, quantity\n");

      // Write out data from the beams
      TACSBVec *q = NULL;
      for ( int k = 0; k < num_steps+1; k++ ){
        TacsScalar X[3*3], vars[8*3], dvars[8*3], ddvars[8*3];
        double time = integrator->getStates(k, &q, NULL, NULL);
        assembler->setVariables(q);
        TACSElement *element = assembler->getElement(elem[pt], X, vars, dvars, ddvars);

        TacsScalar quantity;
        element->evalPointQuantity(elem[pt], TACS_FAILURE_INDEX, time,
                                   0, param[pt], X, vars, dvars, ddvars, &quantity);

        fprintf(fp, "%e  %e %e %e  %e\n",
                time, TacsRealPart(vars[0]), TacsRealPart(vars[1]),
                TacsRealPart(vars[2]), TacsRealPart(quantity));

        // Store 
        data[iq][pt][k] = quantity;
      }
      fclose(fp);
    }

    integrator->decref();
    assembler->decref();

  } // end quadrature

  char filename[128];
  sprintf(filename, "sampling_mean_variance_mid_beam_0.dat");
  FILE *fp = fopen(filename, "w");
          
  // Compute mean and variance of mid point of beam 1
  for (int q = 0; q < nqpoints; q++){
    wq = pc->quadrature(q, zq, yq);
    for (int i = 0; i < num_steps; i++){
      failmeanbar1[i] += wq*data[q][0][i]; // E[F]
      fail2meanbar1[i] += wq*data[q][0][i]*data[q][0][i]; // E{F*F}
    }
  }
  for (int i = 0; i < num_steps; i++){
    failvarbar1[i] = fail2meanbar1[i] - failmeanbar1[i]*failmeanbar1[i]; //E{F^2} - E[f]*E[f]
  }

  // Print mean and variance
  for (int i = 0; i < num_steps; i++){
    double time = i*(12.0/num_steps);
    fprintf(fp, "%e %e %e\n",
            time,
            TacsRealPart(failmeanbar1[i]), 
            TacsRealPart(failvarbar1[i])
            );
  }
  fclose(fp);

  MPI_Finalize();
  return 0;
}
