#include "Linear.hpp"

#include <math.h>

CA::Vector3:: Vector3 ( void )
            : Vector  ( 3    )
{
}

CA::Vector3:: Vector3 ( double * address )
            : Vector  (          address )
{
}

CA::Vector3:: Vector3 ( Vector3 & v )
            : Vector  ( 3           )
{
  V [ 0 ] = v . V [ 0 ] ;
  V [ 1 ] = v . V [ 1 ] ;
  V [ 2 ] = v . V [ 2 ] ;
}

CA::Vector3:: Vector3 (double a,double b,double c)
            : Vector  ( 3                        )
{
  V [ 0 ] = a ;
  V [ 1 ] = b ;
  V [ 2 ] = c ;
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

void CA::Vector3::setValues(double a,double b,double c)
{
  V [ 0 ] = a ;
  V [ 1 ] = b ;
  V [ 2 ] = c ;
}

CA::Vector3 & CA::Vector3::operator = (Vector3 & v)
{
  V [ 0 ] = v . V [ 0 ] ;
  V [ 1 ] = v . V [ 1 ] ;
  V [ 2 ] = v . V [ 2 ] ;
  return (*this)        ;
}

CA::Vector3 & CA::Vector3::operator /= (double v)
{
  V [ 0 ] /= v   ;
  V [ 1 ] /= v   ;
  V [ 2 ] /= v   ;
  return (*this) ;
}

CA::Vector3 & CA::Vector3::operator *= (double v)
{
  V [ 0 ] *= v   ;
  V [ 1 ] *= v   ;
  V [ 2 ] *= v   ;
  return (*this) ;
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

double CA::Vector3::dot(Vector3 & v)
{
  double * U = v . values ( )  ;
  return ( V [ 0 ] * U [ 0 ] ) +
         ( V [ 1 ] * U [ 1 ] ) +
         ( V [ 2 ] * U [ 2 ] ) ;
}

CA::Vector3 CA::Vector3::cross(Vector3 & v)
{
  Vector3  X                                              ;
  double * U = v . values ( )                             ;
  double * W = X . values ( )                             ;
  W [ 0 ] = ( V [ 1 ] * U [ 2 ] ) - ( V [ 2 ] * U [ 1 ] ) ;
  W [ 1 ] = ( V [ 2 ] * U [ 0 ] ) - ( V [ 0 ] * U [ 2 ] ) ;
  W [ 2 ] = ( V [ 0 ] * U [ 1 ] ) - ( V [ 1 ] * U [ 0 ] ) ;
  return X                                                ;
}

double CA::Vector3::square(void)
{
  return ( V [ 0 ] * V [ 0 ] ) +
         ( V [ 1 ] * V [ 1 ] ) +
         ( V [ 2 ] * V [ 2 ] ) ;
}

double CA::Vector3::length(void)
{
  return ::sqrt ( square ( ) ) ;
}

CA::Vector3 & CA::Vector3::normalize(void)
{
  double L = length ( ) ;
  (*this) /= L          ;
  return (*this)        ;
}

CA::Vector3 CA::operator + (CA::Vector3 & a,CA::Vector3 & b)
{
  CA::Vector3 V ( a ) ;
  V += b              ;
  return V            ;
}

CA::Vector3 CA::operator - (CA::Vector3 & a,CA::Vector3 & b)
{
  CA::Vector3 V ( a ) ;
  V -= b              ;
  return V            ;
}

CA::Vector3 CA::operator * (CA::Vector3 & a,double b)
{
  CA::Vector3 V ( a ) ;
  V *= b              ;
  return V            ;
}

CA::Vector3 CA::operator / (CA::Vector3 & a,double b)
{
  CA::Vector3 V ( a ) ;
  V /= b              ;
  return V            ;
}

double CA::operator * (CA::Vector3 & a,CA::Vector3 & b)
{
  double * V = a . values ( )  ;
  double * U = b . values ( )  ;
  return ( V [ 0 ] * U [ 0 ] ) +
         ( V [ 1 ] * U [ 1 ] ) +
         ( V [ 2 ] * U [ 2 ] ) ;
}

CA::Vector3 CA::cross (CA::Vector3 & a,CA::Vector3 & b)
{
  return a . cross ( b ) ;
}
