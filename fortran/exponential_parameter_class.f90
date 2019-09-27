module exponential_parameter_class

  use orthogonal_polynomials, only : laguerre, unit_laguerre
  use gaussian_quadrature   , only : laguerre_quadrature
  
  implicit none

  ! Exponential parameter type
  type :: exponential_parameter
     real(8) :: mu
     real(8) :: beta
   contains
     procedure :: basis
     procedure :: quadrature
  end type exponential_parameter

  ! Constructor interface for list
  interface exponential_parameter
     module procedure create_exponential_parameter
  end interface exponential_parameter

contains

  !===================================================================!
  ! Constructor for exponential parameter
  !===================================================================!
  
  pure type(exponential_parameter) function create_exponential_parameter(mu, beta) &
       & result(this)

    real(8), intent(in) :: mu
    real(8), intent(in) :: beta
    
    this % mu = mu
    this % beta = beta

  end function create_exponential_parameter

  !===================================================================!
  ! Evaluate the basis function and return the value
  !===================================================================!
  
  pure real(8) function basis(this, z, d)

    class(exponential_parameter) , intent(in) :: this
    real(8)                      , intent(in) :: z
    integer                      , intent(in) :: d

    basis = unit_laguerre(z,d)

  end function basis

  !===================================================================!
  ! Return the quadrature points and weights
  !===================================================================!

  pure subroutine quadrature(this, npoints, z, y, w)
    
    class(exponential_parameter) , intent(in)    :: this
    integer                      , intent(in)    :: npoints
    real(8)                      , intent(inout) :: z(:), y(:)
    real(8)                      , intent(inout) :: w(:)

    call laguerre_quadrature(npoints, this % mu, this % sigma, z, y, w)

  end subroutine quadrature
  
end module exponential_parameter_parameter_class

program test_parameters
  
  use exponential_parameter_class

  type(exponential_parameter) :: m
  m = exponential_parameter(a=1.0d0, b=1.0d0)
  print *, m % a
  print *, m % b

end program test_parameters
