/*
  Class to return points and weights for Gaussian Quadrature
  
  Author: Komahan Boopathy (komahanboopathy@gmail.com)
*/

#include <stdio.h>
#include <math.h>
#include "GaussianQuadrature.h"

//===================================================================//
// Constructor and Destructor
//===================================================================//

/*
  Constructor
*/
GaussianQuadrature::GaussianQuadrature(){}

/*
  Destructor
*/
GaussianQuadrature::~GaussianQuadrature(){}


//===================================================================//
// Public functions
//===================================================================//

/*
  Return hermite quadrature points and weights
*/
void GaussianQuadrature::hermiteQuadrature(int npoints, 
                                           double mu, double sigma, 
                                           double *z, double *y, double *w){
  double x[npoints];
  if ( npoints == 1 ){
    // points
    x[0] = 0.0;
    // weights
    w[0] = 1.7724538509055159;
  } else if ( npoints == 2 ){
    // points
    x[0] = -0.7071067811865475;
    x[1] = 0.7071067811865475;
    // weights
    w[0] = 0.8862269254527579;
    w[1] = 0.8862269254527579;
  } else if ( npoints == 3 ){ 
    // points
    x[0] = -1.224744871391589;
    x[1] = 0.0;
    x[2] = 1.224744871391589;
    // weights
    w[0] = 0.2954089751509194;
    w[1] = 1.1816359006036772;
    w[2] = 0.2954089751509194;
  } else if ( npoints == 4 ){
    // points
    x[0] = -1.6506801238857847;
    x[1] = -0.5246476232752904;
    x[2] = 0.5246476232752904;
    x[3] = 1.6506801238857847;
    // weights
    w[0] = 0.08131283544724519;
    w[1] = 0.8049140900055127;
    w[2] = 0.8049140900055127;
    w[3] = 0.08131283544724519;
  } else if ( npoints == 5 ){
    // points
    x[0] = -2.0201828704560856;
    x[1] = -0.9585724646138185;
    x[2] = 0.0;
    x[3] = 0.9585724646138185;
    x[4] = 2.0201828704560856;
    // weights
    w[0] = 0.019953242059045917;
    w[1] = 0.3936193231522411;
    w[2] = 0.9453087204829418;
    w[3] = 0.3936193231522411;
    w[4] = 0.019953242059045917;
  } else if ( npoints == 6 ){
    // points
    x[0] = -2.3506049736744923;
    x[1] = -1.335849074013697;
    x[2] = -0.4360774119276165;
    x[3] = 0.4360774119276165;
    x[4] = 1.335849074013697;
    x[5] = 2.3506049736744923;
    // weights
    w[0] = 0.004530009905508835;
    w[1] = 0.15706732032285647;
    w[2] = 0.7246295952243924;
    w[3] = 0.7246295952243924;
    w[4] = 0.15706732032285647;
    w[5] = 0.004530009905508835;    
  } else if ( npoints == 7 ){
    // points
    x[0] = -2.6519613568352334;
    x[1] = -1.6735516287674714;
    x[2] = -0.8162878828589646;
    x[3] = 0.0;
    x[4] = 0.8162878828589646;
    x[5] = 1.6735516287674714;
    x[6] = 2.6519613568352334;
    // weights
    w[0] = 0.0009717812450995199;
    w[1] = 0.05451558281912705;
    w[2] = 0.4256072526101278;
    w[3] = 0.8102646175568072;
    w[4] = 0.4256072526101278;
    w[5] = 0.05451558281912705;
    w[6] = 0.0009717812450995199;
  } else if ( npoints == 8 ){
    // points
    x[0] = -2.930637420257244;
    x[1] = -1.981656756695843;
    x[2] = -1.1571937124467802;
    x[3] = -0.3811869902073221;
    x[4] = 0.3811869902073221;
    x[5] = 1.1571937124467802;
    x[6] = 1.981656756695843;
    x[7] = 2.930637420257244;    
    // weights
    w[0] = 0.00019960407221136783;
    w[1] = 0.017077983007413467;
    w[2] = 0.20780232581489183;
    w[3] = 0.6611470125582415;
    w[4] = 0.6611470125582415;
    w[5] = 0.20780232581489183;
    w[6] = 0.017077983007413467;
    w[7] = 0.00019960407221136783;
  } else if ( npoints == 9 ){
    // points
    x[0] = -3.1909932017815277;
    x[1] = -2.266580584531843;
    x[2] = -1.468553289216668;
    x[3] = -0.7235510187528376;
    x[4] = 0.0;
    x[5] = 0.7235510187528376;
    x[6] = 1.468553289216668;
    x[7] = 2.266580584531843;
    x[8] = 3.1909932017815277;
    // weights
    w[0] = 3.9606977263264365e-05;
    w[1] = 0.004943624275536941;
    w[2] = 0.08847452739437664;
    w[3] = 0.43265155900255564;
    w[4] = 0.720235215606051;
    w[5] = 0.43265155900255564;
    w[6] = 0.08847452739437664;
    w[7] = 0.004943624275536941;
    w[8] = 3.9606977263264365e-05;
  } else if ( npoints == 10 ){
    // points
    x[0] = -3.4361591188377374;
    x[1] = -2.5327316742327897;
    x[2] = -1.7566836492998816;
    x[3] = -1.0366108297895136;
    x[4] = -0.3429013272237046;
    x[5] = 0.3429013272237046;
    x[6] = 1.0366108297895136;
    x[7] = 1.7566836492998816;
    x[8] = 2.5327316742327897;
    x[9] = 3.4361591188377374;
    // weights
    w[0] = 7.640432855232641e-06;
    w[1] = 0.0013436457467812324;
    w[2] = 0.033874394455481106;
    w[3] = 0.2401386110823147;
    w[4] = 0.6108626337353258;
    w[5] = 0.6108626337353258;
    w[6] = 0.2401386110823147;
    w[7] = 0.033874394455481106;
    w[8] = 0.0013436457467812324;
    w[9] = 7.640432855232641e-06;
  } else {
    printf("Error: Implement Hermite quadrature points\n");
  }

  // Return points in appropriate domains
  for ( int n = 0; n < npoints; n++ ) {
    y[n] = mu + sigma*pow(2.0,0.5)*x[n];
    z[n] = (y[n] - mu)/sigma;
    w[n] = w[n]/pow(4.0*atan(1.0),0.5);
  }
}

/*
  Return legendre quadrature points and weights
*/
void GaussianQuadrature::legendreQuadrature(int npoints, 
                                            double a, double b, 
                                            double *z, double *y, double *w){
  double x[npoints];
  if ( npoints == 1 ){
    // points
    x[0] = 0.0;
    // weights
    w[0] = 2.0;
  } else if ( npoints == 2 ){
    // points
    x[0] = -0.5773502691896257;
    x[1] = 0.5773502691896257;
    // weights
    w[0] = 1.0;
    w[1] = 1.0;
  } else if ( npoints == 3 ){
    // points
    x[0] = -0.7745966692414834;
    x[1] = 0.0;
    x[2] = 0.7745966692414834;
    // weights
    w[0] = 0.5555555555555557;
    w[1] = 0.8888888888888888;
    w[2] = 0.5555555555555557;
  } else if ( npoints == 4 ){
    // points
    x[0] = -0.8611363115940526;
    x[1] = -0.33998104358485626;
    x[2] = 0.33998104358485626;
    x[3] = 0.8611363115940526;
    // weights
    w[0] = 0.3478548451374537;
    w[1] = 0.6521451548625462;
    w[2] = 0.6521451548625462;
    w[3] = 0.3478548451374537;
  } else if ( npoints == 5 ){
    // points
    x[0] = -0.906179845938664;
    x[1] = -0.5384693101056831;
    x[2] = 0.0;
    x[3] = 0.5384693101056831;
    x[4] = 0.906179845938664;
    // weights
    w[0] = 0.23692688505618942;
    w[1] = 0.4786286704993662;
    w[2] = 0.568888888888889;
    w[3] = 0.4786286704993662;
    w[4] = 0.23692688505618942;
  } else if ( npoints == 6 ){
    // points
    x[0] = -0.932469514203152;
    x[1] = -0.6612093864662645;
    x[2] = -0.23861918608319693;
    x[3] = 0.23861918608319693;
    x[4] = 0.6612093864662645;
    x[5] = 0.932469514203152;
    // weights
    w[0] = 0.17132449237916975;
    w[1] = 0.36076157304813894;
    w[2] = 0.46791393457269137;
    w[3] = 0.46791393457269137;
    w[4] = 0.36076157304813894;
    w[5] = 0.17132449237916975;
  } else if ( npoints == 7 ){
    // points
    x[0] = -0.9491079123427585;
    x[1] = -0.7415311855993945;
    x[2] = -0.4058451513773972;
    x[3] = 0.0;
    x[4] = 0.4058451513773972;
    x[5] = 0.7415311855993945;
    x[6] = 0.9491079123427585;
    // weights
    w[0] = 0.12948496616887065;
    w[1] = 0.2797053914892766;
    w[2] = 0.3818300505051183;
    w[3] = 0.41795918367346896;
    w[4] = 0.3818300505051183;
    w[5] = 0.2797053914892766;
    w[6] = 0.12948496616887065;
  } else if ( npoints == 8 ){
    // points
    x[0] = -0.9602898564975362;
    x[1] = -0.7966664774136267;
    x[2] = -0.525532409916329;
    x[3] = -0.18343464249564978;
    x[4] = 0.18343464249564978;
    x[5] = 0.525532409916329;
    x[6] = 0.7966664774136267;
    x[7] = 0.9602898564975362;
    // weights
    w[0] = 0.10122853629037669;
    w[1] = 0.22238103445337434;
    w[2] = 0.31370664587788705;
    w[3] = 0.36268378337836177;
    w[4] = 0.36268378337836177;
    w[5] = 0.31370664587788705;
    w[6] = 0.22238103445337434;
    w[7] = 0.10122853629037669;
  } else if ( npoints == 9 ){
    // points
    x[0] = -0.9681602395076261;
    x[1] = -0.8360311073266358;
    x[2] = -0.6133714327005904;
    x[3] = -0.3242534234038089;
    x[4] = 0.0;
    x[5] = 0.3242534234038089;
    x[6] = 0.6133714327005904;
    x[7] = 0.8360311073266358;
    x[8] = 0.9681602395076261;
    // weights
    w[0] = 0.08127438836157472;
    w[1] = 0.18064816069485712;
    w[2] = 0.26061069640293566;
    w[3] = 0.3123470770400028;
    w[4] = 0.33023935500125967;
    w[5] = 0.3123470770400028;
    w[6] = 0.26061069640293566;
    w[7] = 0.18064816069485712;
    w[8] = 0.08127438836157472;
  } else if ( npoints == 10 ){
    // points
    x[0] = -0.9739065285171717;
    x[1] = -0.8650633666889845;
    x[2] = -0.6794095682990244;
    x[3] = -0.4333953941292472;
    x[4] = -0.14887433898163122;
    x[5] = 0.14887433898163122;
    x[6] = 0.4333953941292472;
    x[7] = 0.6794095682990244;
    x[8] = 0.8650633666889845;
    x[9] = 0.9739065285171717;
    // weights
    w[0] = 0.06667134430868807;
    w[1] = 0.14945134915058036;
    w[2] = 0.219086362515982;
    w[3] = 0.2692667193099965;
    w[4] = 0.295524224714753;
    w[5] = 0.295524224714753;
    w[6] = 0.2692667193099965;
    w[7] = 0.219086362515982;
    w[8] = 0.14945134915058036;
    w[9] = 0.06667134430868807;
  } else {
    printf("Error: Implement Legendre quadrature points\n");
  }

  // Return points in appropriate domains
  double shift = (b+a)/2.0;
  double scale = (b-a)/2.0;
  for ( int n = 0; n < npoints; n++ ) {
    y[n] = scale*x[n] + shift;
    z[n] = (y[n]-a)/(b-a);
    w[n] = w[n]/2.0;
  }
}

/*
  Return laguerre quadrature points and weights
*/
void GaussianQuadrature::laguerreQuadrature(int npoints, 
                                            double mu, double beta, 
                                            double *z, double *y, double *w){
  double x[npoints];
  if ( npoints == 1 ){
    // points
    x[0] = 1.0;
    // weights
    w[0] = 1.0;
  } else if ( npoints == 2 ){
    // points
    x[0] = 0.585786437626905;
    x[1] = 3.414213562373095;
    // weights
    w[0] = 0.8535533905932737;
    w[1] = 0.14644660940672624;
  } else if ( npoints == 3 ){
    // points
    x[0] = 0.4157745567834791;
    x[1] = 2.294280360279042;
    x[2] = 6.2899450829374794;
    // weights
    w[0] = 0.7110930099291729;
    w[1] = 0.278517733569241;
    w[2] = 0.010389256501586133;
  } else if ( npoints == 4 ){
    // points
    x[0] = 0.3225476896193924;
    x[1] = 1.7457611011583465;
    x[2] = 4.536620296921128;
    x[3] = 9.395070912301133;
    // weights
    w[0] = 0.6031541043416337;
    w[1] = 0.35741869243779956;
    w[2] = 0.038887908515005405;
    w[3] = 0.0005392947055613296;
  } else if ( npoints == 5 ){
    // points
    x[0] = 0.26356031971814087;
    x[1] = 1.4134030591065168;
    x[2] = 3.596425771040722;
    x[3] = 7.085810005858837;
    x[4] = 12.640800844275782;
    // weights
    w[0] = 0.5217556105828085;
    w[1] = 0.398666811083176;
    w[2] = 0.07594244968170769;
    w[3] = 0.0036117586799220545;
    w[4] = 2.3369972385776248e-05;
  } else if ( npoints == 6 ){
    // points
    x[0] = 0.2228466041792607;
    x[1] = 1.1889321016726226;
    x[2] = 2.992736326059314;
    x[3] = 5.77514356910451;
    x[4] = 9.83746741838259;
    x[5] = 15.982873980601703;
    // weights
    w[0] = 0.45896467394996476;
    w[1] = 0.41700083077212;
    w[2] = 0.11337338207404488;
    w[3] = 0.010399197453149087;
    w[4] = 0.00026101720281493265;
    w[5] = 8.985479064296213e-07;
  } else if ( npoints == 7 ){
    // points
    x[0] = 0.19304367656036225;
    x[1] = 1.0266648953391924;
    x[2] = 2.567876744950746;
    x[3] = 4.900353084526484;
    x[4] = 8.18215344456286;
    x[5] = 12.734180291797815;
    x[6] = 19.39572786226254;
    // weights
    w[0] = 0.40931895170127336;
    w[1] = 0.4218312778617202;
    w[2] = 0.1471263486575053;
    w[3] = 0.020633514468716942;
    w[4] = 0.001074010143280746;
    w[5] = 1.5865464348564196e-05;
    w[6] = 3.1703154789955624e-08;
  } else if ( npoints == 8 ){
    // points
    x[0] = 0.17027963230510093;
    x[1] = 0.90370177679938;
    x[2] = 2.251086629866131;
    x[3] = 4.266700170287659;
    x[4] = 7.0459054023934655;
    x[5] = 10.758516010180996;
    x[6] = 15.740678641278004;
    x[7] = 22.863131736889265;
    // weights
    w[0] = 0.36918858934163495;
    w[1] = 0.4187867808143447;
    w[2] = 0.17579498663717255;
    w[3] = 0.033343492261215794;
    w[4] = 0.0027945362352256834;
    w[5] = 9.076508773358139e-05;
    w[6] = 8.48574671627257e-07;
    w[7] = 1.0480011748715153e-09;
  } else if ( npoints == 9 ){
    // points
    x[0] = 0.1523222277318084;
    x[1] = 0.8072200227422562;
    x[2] = 2.005135155619347;
    x[3] = 3.783473973331233;
    x[4] = 6.204956777876613;
    x[5] = 9.372985251687576;
    x[6] = 13.466236911092095;
    x[7] = 18.833597788991696;
    x[8] = 26.374071890927375;
    // weights
    w[0] = 0.33612642179796287;
    w[1] = 0.4112139804239856;
    w[2] = 0.1992875253708841;
    w[3] = 0.04746056276565138;
    w[4] = 0.005599626610794551;
    w[5] = 0.00030524976709320943;
    w[6] = 6.592123026075329e-06;
    w[7] = 4.1107693303495754e-08;
    w[8] = 3.290874030350679e-11;
  } else if ( npoints == 10 ){
    // points
    x[0] = 0.1377934705404926;
    x[1] = 0.729454549503171;
    x[2] = 1.8083429017403159;
    x[3] = 3.4014336978548996;
    x[4] = 5.552496140063804;
    x[5] = 8.330152746764497;
    x[6] = 11.843785837900066;
    x[7] = 16.279257831378104;
    x[8] = 21.99658581198076;
    x[9] = 29.92069701227389;
    // weights
    w[0] = 0.3084411157650173;
    w[1] = 0.4011199291552761;
    w[2] = 0.2180682876118096;
    w[3] = 0.062087456098677773;
    w[4] = 0.0095015169751811;
    w[5] = 0.0007530083885875384;
    w[6] = 2.8259233495995642e-05;
    w[7] = 4.249313984962698e-07;
    w[8] = 1.839564823979633e-09;
    w[9] = 9.91182721960906e-13;
  } else {
    printf("Error: Implement Laguerre quadrature points\n");
  }

  // Return points in appropriate domains
  for ( int n = 0; n < npoints; n++ ) {
    y[n] = mu + beta*x[n];
    z[n] = x[n];
  }
}

int main(int argc, char *argv[] ){

  // Create quadrature object
  GaussianQuadrature *gaussQuad = new GaussianQuadrature();
  
  // Allocate memory on heap
  int npoints = 10;
  double *z = new double[npoints];
  double *y = new double[npoints];
  double *w = new double[npoints];

  // Hermite Quadrature
  double mun = 0.0;
  double sigman = 1.0;
  gaussQuad->hermiteQuadrature(npoints, mun, sigman, 
                               &z[0], &y[0], &w[0]);  
  printf("Hermite Quadrature\n");
  double wsum = 0.0;
  for ( int i = 0 ; i < npoints; i++ ){
    wsum += w[i];
    printf("%d %15.6f %15.6f %15.6f %15.6f\n", i, z[i], y[i], w[i], wsum);
  }

  // Legendre Quadrature
  double a = 0.0;
  double b = 1.0;
  gaussQuad->legendreQuadrature(npoints, a, b, 
                                &z[0], &y[0], &w[0]);  
  printf("\nLegendre Quadrature\n");
  wsum = 0.0;
  for ( int i = 0 ; i < npoints; i++ ){
    wsum += w[i];
    printf("%d %15.6f %15.6f %15.6f %15.6f\n", i, z[i], y[i], w[i], wsum);
  }

  // Laguerre Quadrature
  double mu = 0.0;
  double beta = 1.0;
  gaussQuad->laguerreQuadrature(npoints, mu, beta, 
                                &z[0], &y[0], &w[0]);  
  printf("\nLaguerre Quadrature\n");
  wsum = 0.0;
  for ( int i = 0 ; i < npoints; i++ ){
    wsum += w[i];
    printf("%d %15.6f %15.6f %15.6f %15.6f\n", i, z[i], y[i], w[i], wsum);
  }

  // Free allocated heap memory
  delete gaussQuad;
  delete[] z;
  delete[] y;
  delete[] w;
}