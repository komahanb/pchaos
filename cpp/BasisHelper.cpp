#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<list>
#include<vector>

#include"BasisHelper.h"
#include"ArrayList.h"

using namespace std;

// Constructor and Destructor
BasisHelper::BasisHelper(){}
BasisHelper::~BasisHelper(){}

/*
  Return the index set corresponding to maximum degrees of each parameter
*/
void BasisHelper::basisDegrees(const int nvars, const int *pmax, 
                               int *nindices, int **indx){
  if ( nvars == 1 ) {
    univariateBasisDegrees(nvars, pmax, nindices, indx);
  } else if ( nvars == 2 ) {
    bivariateBasisDegrees(nvars, pmax, nindices, indx);
  } else if ( nvars == 3 ) {
    trivariateBasisDegrees(nvars, pmax, nindices, indx);
  } else if ( nvars == 4 ) {
    quadvariateBasisDegrees(nvars, pmax, nindices, indx);
  } else if ( nvars == 5 ) {   
    pentavariateBasisDegrees(nvars, pmax, nindices, indx);
  } else {
    printf("Basis not implemented for more than five variables");
  }
}

/*
  Helps determine whether the evaluation is necessary as many terms
  are non-zero in jacobian matrix
*/
void BasisHelper::sparse(const int nvars, 
                         int *dmapi, int *dmapj, int *dmapk, 
                         bool *filter){
  for( int i = 0; i < nvars; i++ ){
    if (abs(dmapi[i] - dmapj[i]) <= dmapk[i]){
      filter[i] = true;
    } else {
      filter[i] = false;
    }
  }
}

void BasisHelper::univariateBasisDegrees(const int nvars, const int *pmax, 
                                         int *nindices, int **indx){
}

void BasisHelper::bivariateBasisDegrees(const int nvars, const int *pmax, 
                                        int *nindices, int **indx){
  // Number of terms from tensor product
  int nterms = 1;
  for (int i = 0; i < nvars; i++){
    nterms *= 1 + pmax[i];
  }

  int num_total_degrees = 1;
  for (int i = 0; i < nvars; i++){
    num_total_degrees += pmax[i];
  }

  // Create a map of empty array lists
  std::map<int,ArrayList*> dmap;
  for (int k = 0; k < num_total_degrees; k++){
    dmap.insert(pair<int, ArrayList*>(k, new ArrayList(nterms, nvars)));
  }

  // Add degree wise tuples into each arraylist
  for (int ii = 0; ii <= pmax[0]; ii++){
    for (int jj = 0; jj <= pmax[1]; jj++){
      int tuple[] = {ii,jj};
      dmap[ii+jj]->addEntry(tuple);
    }
  }

  int ctr = 0;
  for (int k = 0; k < num_total_degrees; k++){    
    int nrecords = dmap[k]->getNumEntries();
    dmap[k]->getEntries(&indx[ctr]);
    ctr = ctr + nrecords;
  }  
  nindices[0] = ctr;

  /*
  ArrayList **degree_list = NULL;
  for (int k = 0; k < num_total_degrees; k++){
    degree_list[k] = new ArrayList(nterms, nvars);
  }

  return;
  for (int ii = 0; ii < pmax[0]; ii++){
    for (int jj = 0; jj < pmax[1]; jj++){
      printf("adding %d %d \n", ii, jj);
      int tuple[] = {ii,jj};
      degree_list[ii+jj]->addEntry(tuple);
    }
  }
  
  // Flatten list and return into indx
  int ctr = 0;
  for (int k = 0; k < num_total_degrees; k++){    
    int nrecords = degree_list[k]->getNumEntries();
    degree_[k]->getEntries(&indx[ctr]);
    ctr = ctr + nrecords;
  }  
  nindices[0] = ctr;
  */
  
}

void BasisHelper::trivariateBasisDegrees(const int nvars, const int *pmax, 
                                         int *nindices, int **indx){}
void BasisHelper::quadvariateBasisDegrees(const int nvars, const int *pmax, 
                                          int *nindices, int **indx){}
void BasisHelper::pentavariateBasisDegrees(const int nvars, const int *pmax, 
                                           int *nindices, int **indx){}
