#include "Linear.hpp"

CA::Vector3:: Vector3 ( void )
            : Vector  ( 3    )
{
}

CA::Vector3::~Vector3 (void)
{
}

int CA::Vector3::type(void) const
{
  return 3 ;
}

void CA::Vector3::zero(void)
{
  V [ 0 ] = 0.0 ;
  V [ 1 ] = 0.0 ;
  V [ 2 ] = 0.0 ;
}

CA::Vector3 & CA::Vector3::operator += (Vector3 & v)
{
  V [ 0 ] += v . V [ 0 ] ;
  V [ 1 ] += v . V [ 1 ] ;
  V [ 2 ] += v . V [ 2 ] ;
  return (*this)         ;
}

CA::Vector3 & CA::Vector3::operator -= (Vector3 & v)
{
  V [ 0 ] -= v . V [ 0 ] ;
  V [ 1 ] -= v . V [ 1 ] ;
  V [ 2 ] -= v . V [ 2 ] ;
  return (*this)         ;
}
