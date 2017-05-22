#include "Coordinate.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

CA::Spherical:: Spherical (void)
{
}

CA::Spherical::~Spherical (void)
{
}

CA::Vector4 CA::Spherical::toCartesian (Vector4 & s)
{
  double * v  = s . values ( )         ;
  double   r  = v [ 3 ]                ;
  double   a  = v [ 0 ] * M_PI / 180.0 ;
  double   b  = v [ 1 ] * M_PI / 180.0 ;
  double   as = FastSin ( a ) * r      ;
  double   ac = FastCos ( a ) * r      ;
  double   bs = FastSin ( b )          ;
  double   bc = FastCos ( b )          ;
  Vector4  c                           ;
  //////////////////////////////////////
  v       = c . values ( )             ;
  v [ 0 ] = as * bc                    ;
  v [ 1 ] = as * bs                    ;
  v [ 2 ] = ac                         ;
  v [ 3 ] = 1.0                        ;
  //////////////////////////////////////
  return c                             ;
}

CA::Vector4 CA::Spherical::toSpherical (Vector4 & c)
{
  double * v  = c . values ( )                 ;
  double   x  = v [ 0 ]                        ;
  double   y  = v [ 1 ]                        ;
  double   z  = v [ 2 ]                        ;
  double   x2 = x * x                          ;
  double   y2 = y * y                          ;
  double   z2 = z * z                          ;
  double   r2 = x2 + y2 + z2                   ;
  double   r  = ::sqrt ( r2 )                  ;
  double   a  = acos  ( z / r ) * 180.0 / M_PI ;
  double   b  = atan2 ( y , x ) * 180.0 / M_PI ;
  Vector4  s                                   ;
  //////////////////////////////////////////////
  v       = s . values ( )                     ;
  v [ 0 ] = a                                  ;
  v [ 1 ] = b                                  ;
  v [ 2 ] = 0.0                                ;
  v [ 3 ] = r                                  ;
  //////////////////////////////////////////////
  return s                                     ;
}
