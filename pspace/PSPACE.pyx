# distutils: language = c++
from PSPACE cimport *

# Import numpy
cimport numpy as np
import numpy as np
np.import_array()

# Import C methods for python
from cpython cimport PyObject, Py_INCREF, Py_DECREF

include "PspaceDefs.pxi"

cdef inplace_array_1d(int nptype, int dim1, void *data_ptr):
    '''
    Return a numpy version of the array
    '''
    cdef int size = 1
    cdef np.npy_intp shape[1]
    cdef np.ndarray ndarray
    shape[0] = <np.npy_intp>dim1
    ndarray = np.PyArray_SimpleNewFromData(size, shape, nptype, data_ptr)
    return ndarray

cdef class PyAbstractParameter:
    def __cinit__(self):
        self.ptr = NULL
        return
    def basis(self, scalar z, int d):
        return self.ptr.basis(z,d)

cdef class PyParameterFactory:
    def __cinit__(self):
        self.ptr = new ParameterFactory()
        return
    def createNormalParameter(self, scalar mu, scalar sigma, int dmax):
        cdef PyAbstractParameter pyparam = PyAbstractParameter()
        pyparam.ptr = self.ptr.createNormalParameter(mu, sigma, dmax)
        return pyparam
    def createUniformParameter(self, scalar a, scalar b, int dmax):
        cdef PyAbstractParameter pyparam = PyAbstractParameter()
        pyparam.ptr = self.ptr.createUniformParameter(a, b, dmax)
        return pyparam
    def createExponentialParameter(self, scalar mu, scalar beta, int dmax):
        cdef PyAbstractParameter pyparam = PyAbstractParameter()
        pyparam.ptr = self.ptr.createExponentialParameter(mu, beta, dmax)
        return pyparam

cdef class PyParameterContainer:
    def __cinit__(self, int basis_type=0, int quadrature_type=0):
        self.ptr = new ParameterContainer(basis_type, quadrature_type)
        return

    def addParameter(self, PyAbstractParameter param):
        self.ptr.addParameter(param.ptr)
        return

    def basis(self, int k, np.ndarray[scalar, ndim=1, mode='c'] z):
        return self.ptr.basis(k, <scalar*> z.data)
    def quadrature(self, int q):
        nparams = self.getNumParameters()
        cdef np.ndarray yq = None
        cdef np.ndarray zq = None
        yq = np.zeros(nparams, dtype=dtype)
        zq = np.zeros(nparams, dtype=dtype)
        wq = self.ptr.quadrature(q, <scalar*> zq.data, <scalar*> yq.data)
        return wq, zq, yq

    def getNumBasisTerms(self):
        return self.ptr.getNumBasisTerms()
    def getNumParameters(self):
        return self.ptr.getNumParameters()
    def getNumQuadraturePoints(self):
        return self.ptr.getNumQuadraturePoints()

    def getBasisParamDeg(self, int k):
        nparams = self.getNumParameters()
        cdef np.ndarray degs = None
        degs = np.zeros(nparams, dtype=np.intc)
        self.ptr.getBasisParamDeg(k, <int*> degs.data)
        return degs
    def getBasisParamMaxDeg(self):
        nparams = self.getNumParameters()
        cdef np.ndarray pmax = None
        pmax = np.zeros(nparams, dtype=np.intc)
        self.ptr.getBasisParamMaxDeg(<int*> pmax.data)
        return pmax

    def initialize(self):
        self.ptr.initialize()
        return
    def initializeBasis(self, np.ndarray[int, ndim=1, mode='c'] pmax):
        self.ptr.initializeBasis(<int*> pmax.data)
        return
    def initializeQuadrature(self, np.ndarray[int, ndim=1, mode='c'] nqpts):
        self.ptr.initializeQuadrature(<int*> nqpts.data)
        return
