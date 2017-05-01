#include "Linear.hpp"

#include <math.h>

CA::Vector4:: Vector4 ( void )
            : Vector  ( 4    )
{
}

CA::Vector4:: Vector4 ( double * address )
            : Vector  (          address )
{
}

CA::Vector4:: Vector4 ( Vector3 & v )
            : Vector  ( 4           )
{
  double * U               ;
  U       = v . values ( ) ;
  V [ 0 ] = U [ 0 ]        ;
  V [ 1 ] = U [ 1 ]        ;
  V [ 2 ] = U [ 2 ]        ;
  V [ 3 ] =     0          ;
}

CA::Vector4:: Vector4 ( Vector4 & v )
            : Vector  ( 4           )
{
  V [ 0 ] = v . V [ 0 ] ;
  V [ 1 ] = v . V [ 1 ] ;
  V [ 2 ] = v . V [ 2 ] ;
  V [ 3 ] = v . V [ 3 ] ;
}

CA::Vector4:: Vector4 ( double a , double b , double c , double d )
            : Vector  ( 4                                         )
{
  V [ 0 ] = a ;
  V [ 1 ] = b ;
  V [ 2 ] = c ;
  V [ 3 ] = d ;
}

CA::Vector4::~Vector4 (void)
{
}

int CA::Vector4::type(void) const
{
  return 4 ;
}

void CA::Vector4::zero(void)
{
  V [ 0 ] = 0.0 ;
  V [ 1 ] = 0.0 ;
  V [ 2 ] = 0.0 ;
  V [ 3 ] = 0.0 ;
}

void CA::Vector4::setValues(double a,double b,double c,double d)
{
  V [ 0 ] = a ;
  V [ 1 ] = b ;
  V [ 2 ] = c ;
  V [ 3 ] = d ;
}

CA::Vector4 & CA::Vector4::operator = (Vector4 & v)
{
  V [ 0 ] = v . V [ 0 ] ;
  V [ 1 ] = v . V [ 1 ] ;
  V [ 2 ] = v . V [ 2 ] ;
  V [ 3 ] = v . V [ 3 ] ;
  return (*this)        ;
}

CA::Vector4 & CA::Vector4::operator /= (double v)
{
  V [ 0 ] /= v   ;
  V [ 1 ] /= v   ;
  V [ 2 ] /= v   ;
  V [ 3 ] /= v   ;
  return (*this) ;
}

CA::Vector4 & CA::Vector4::operator *= (double v)
{
  V [ 0 ] *= v   ;
  V [ 1 ] *= v   ;
  V [ 2 ] *= v   ;
  V [ 3 ] *= v   ;
  return (*this) ;
}

CA::Vector4 & CA::Vector4::operator += (Vector4 & v)
{
  V [ 0 ] += v . V [ 0 ] ;
  V [ 1 ] += v . V [ 1 ] ;
  V [ 2 ] += v . V [ 2 ] ;
  V [ 3 ] += v . V [ 3 ] ;
  return (*this)         ;
}

CA::Vector4 & CA::Vector4::operator -= (Vector4 & v)
{
  V [ 0 ] -= v . V [ 0 ] ;
  V [ 1 ] -= v . V [ 1 ] ;
  V [ 2 ] -= v . V [ 2 ] ;
  V [ 3 ] -= v . V [ 3 ] ;
  return (*this)         ;
}

double CA::Vector4::dot(Vector4 & v)
{
  double * U = v . values ( )  ;
  return ( V [ 0 ] * U [ 0 ] ) +
         ( V [ 1 ] * U [ 1 ] ) +
         ( V [ 2 ] * U [ 2 ] ) +
         ( V [ 3 ] * U [ 3 ] ) ;
}

CA::Vector4 CA::Vector4::cross(Vector4 & v)
{
  Vector4  X                                              ;
  double * U = v . values ( )                             ;
  double * W = X . values ( )                             ;
  W [ 0 ] = ( V [ 1 ] * U [ 2 ] ) - ( V [ 2 ] * U [ 1 ] ) ;
  W [ 1 ] = ( V [ 2 ] * U [ 0 ] ) - ( V [ 0 ] * U [ 2 ] ) ;
  W [ 2 ] = ( V [ 0 ] * U [ 1 ] ) - ( V [ 1 ] * U [ 0 ] ) ;
  W [ 3 ] = 0                                             ;
  return X                                                ;
}

CA::Vector4 CA::Vector4::cross(Vector4 & v,double d)
{
  Vector4  X                                              ;
  double * U = v . values ( )                             ;
  double * W = X . values ( )                             ;
  W [ 0 ] = ( V [ 1 ] * U [ 2 ] ) - ( V [ 2 ] * U [ 1 ] ) ;
  W [ 1 ] = ( V [ 2 ] * U [ 0 ] ) - ( V [ 0 ] * U [ 2 ] ) ;
  W [ 2 ] = ( V [ 0 ] * U [ 1 ] ) - ( V [ 1 ] * U [ 0 ] ) ;
  W [ 3 ] = d                                             ;
  return X                                                ;
}

double CA::Vector4::square(void)
{
  return ( V [ 0 ] * V [ 0 ] ) +
         ( V [ 1 ] * V [ 1 ] ) +
         ( V [ 2 ] * V [ 2 ] ) +
         ( V [ 3 ] * V [ 3 ] ) ;
}

double CA::Vector4::length(void)
{
  return ::sqrt ( square ( ) ) ;
}

CA::Vector4 & CA::Vector4::normalize(void)
{
  double L = length ( ) ;
  (*this) /= L          ;
  return (*this)        ;
}

CA::Vector4 CA::operator + (CA::Vector4 & a,CA::Vector4 & b)
{
  CA::Vector4 V ( a ) ;
  V += b              ;
  return V            ;
}

CA::Vector4 CA::operator - (CA::Vector4 & a,CA::Vector4 & b)
{
  CA::Vector4 V ( a ) ;
  V -= b              ;
  return V            ;
}

CA::Vector4 CA::operator * (CA::Vector4 & a,double b)
{
  CA::Vector4 V ( a ) ;
  V *= b              ;
  return V            ;
}

CA::Vector4 CA::operator / (CA::Vector4 & a,double b)
{
  CA::Vector4 V ( a ) ;
  V /= b              ;
  return V            ;
}

double CA::operator * (CA::Vector4 & a,CA::Vector4 & b)
{
  double * V = a . values ( )  ;
  double * U = b . values ( )  ;
  return ( V [ 0 ] * U [ 0 ] ) +
         ( V [ 1 ] * U [ 1 ] ) +
         ( V [ 2 ] * U [ 2 ] ) +
         ( V [ 3 ] * U [ 3 ] ) ;
}

CA::Vector4 CA::cross (CA::Vector4 & a,CA::Vector4 & b)
{
  return a . cross ( b ) ;
}
