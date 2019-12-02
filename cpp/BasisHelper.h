#ifndef BASIS_HELPER
#define BASIS_HELPER

#include "scalar.h"

class BasisHelper{
 public:
  // Constructor and destructor
  BasisHelper();
  ~BasisHelper();

  // Find tensor product of 1d rules
  void basisDegrees(const int nvars, const int *pmax, int *nindices, int **indx);
  void sparse(const int nvars, int *dmapi, int *dmapj, int *dmapk, 
              bool *sparse);

 private:
  void univariateBasisDegrees(const int nvars, const int *pmax, int *nindices, int **indx);
  void bivariateBasisDegrees(const int nvars, const int *pmax, int *nindices, int **indx);
  void trivariateBasisDegrees(const int nvars, const int *pmax, int *nindices, int **indx);
  void quadvariateBasisDegrees(const int nvars, const int *pmax, int *nindices, int **indx);
  void pentavariateBasisDegrees(const int nvars, const int *pmax, int *nindices, int **indx);
};

#endif
