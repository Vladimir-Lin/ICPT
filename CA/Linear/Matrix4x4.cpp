#include "Linear.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

CA::Matrix4x4:: Matrix4x4 (void)
{
}

CA::Matrix4x4::~Matrix4x4 (void)
{
}

double * CA::Matrix4x4::values(void)
{
  return M ;
}

CA::Matrix4x4 & CA::Matrix4x4::zero(void)
{
  ::memset ( M , 0 , sizeof(double) * 16 ) ;
  return (*this)                           ;
}

CA::Matrix4x4 & CA::Matrix4x4::identity(void)
{
  M [  0 ] = 1 ; M [  1 ] = 0 ; M [  2 ] = 0 ; M [  3 ] = 0 ;
  M [  4 ] = 0 ; M [  5 ] = 1 ; M [  6 ] = 0 ; M [  7 ] = 0 ;
  M [  8 ] = 0 ; M [  9 ] = 0 ; M [ 10 ] = 1 ; M [ 11 ] = 0 ;
  M [ 12 ] = 0 ; M [ 13 ] = 0 ; M [ 14 ] = 0 ; M [ 15 ] = 1 ;
  return (*this)                                            ;
}

CA::Matrix4x4 & CA::Matrix4x4::operator * (double v)
{
  for ( int i = 0 ; i < 16 ; i++ ) {
    M [ i ] *= v                   ;
  }                                ;
  return (*this)                   ;
}

CA::Matrix4x4 & CA::Matrix4x4::operator / (double v)
{
  for ( int i = 0 ; i < 16 ; i++ ) {
    M [ i ] /= v                   ;
  }                                ;
  return (*this)                   ;
}

CA::Matrix4x4 & CA::Matrix4x4::operator += (Matrix4x4 & v)
{
  for ( int i = 0 ; i < 16 ; i++ ) {
    M [ i ] += v . M [ i ]         ;
  }                                ;
  return (*this)                   ;
}

CA::Matrix4x4 & CA::Matrix4x4::operator -= (Matrix4x4 & v)
{
  for ( int i = 0 ; i < 16 ; i++ ) {
    M [ i ] -= v . M [ i ]         ;
  }                                ;
  return (*this)                   ;
}

CA::Matrix4x4 & CA::Matrix4x4::translate(Vector4 & v)
{
  double * P = v . values ( )                                     ;
  M [  0 ] = 1 ; M [  1 ] = 0 ; M [  2 ] = 0 ; M [  3 ] = P [ 0 ] ;
  M [  4 ] = 0 ; M [  5 ] = 1 ; M [  6 ] = 0 ; M [  7 ] = P [ 1 ] ;
  M [  8 ] = 0 ; M [  9 ] = 0 ; M [ 10 ] = 1 ; M [ 11 ] = P [ 2 ] ;
  M [ 12 ] = 0 ; M [ 13 ] = 0 ; M [ 14 ] = 0 ; M [ 15 ] = 1       ;
  return (*this)                                                  ;
}

CA::Matrix4x4 & CA::Matrix4x4::scale(Vector4 & v)
{
  double * S = v . values ( )                                                       ;
  M [  0 ] = S [ 0 ] ; M [  1 ] = 0       ; M [  2 ] = 0       ; M [  3 ] = 0       ;
  M [  4 ] = 0       ; M [  5 ] = S [ 1 ] ; M [  6 ] = 0       ; M [  7 ] = 0       ;
  M [  8 ] = 0       ; M [  9 ] = 0       ; M [ 10 ] = S [ 2 ] ; M [ 11 ] = 0       ;
  M [ 12 ] = 0       ; M [ 13 ] = 0       ; M [ 14 ] = 0       ; M [ 15 ] = S [ 3 ] ;
  return (*this)                                                                    ;
}

CA::Matrix4x4 & CA::Matrix4x4::rotate(Vector4 & v)
{
  double * R    = v . values ( )                                             ;
  double   x    = R [ 0 ]                                                    ;
  double   y    = R [ 1 ]                                                    ;
  double   z    = R [ 2 ]                                                    ;
  double   w    = R [ 3 ] * M_PI / 180                                       ;
  double   x2   = x * x                                                      ;
  double   y2   = y * y                                                      ;
  double   z2   = z * z                                                      ;
  double   xy   = x * y                                                      ;
  double   xz   = x * z                                                      ;
  double   yz   = y * z                                                      ;
  double   sw   = FastSin ( w )                                              ;
  double   cw   = FastCos ( w )                                              ;
  double   mc   = 1  - cw    /* 1 - cos ( w ) */                             ;
  double   swx  = sw * x     /* sin ( w ) * x */                             ;
  double   swy  = sw * y     /* sin ( w ) * y */                             ;
  double   swz  = sw * z     /* sin ( w ) * z */                             ;
  double   mcxy = mc * xy    /* ( 1 - cos ( w ) ) * xy */                    ;
  double   mcxz = mc * xz    /* ( 1 - cos ( w ) ) * xz */                    ;
  double   mcyz = mc * yz    /* ( 1 - cos ( w ) ) * yz */                    ;
  double   mcx2 = mc * x2    /* ( 1 - cos ( w ) ) * xx */                    ;
  double   mcy2 = mc * y2    /* ( 1 - cos ( w ) ) * yy */                    ;
  double   mcz2 = mc * z2    /* ( 1 - cos ( w ) ) * zz */                    ;
  ////////////////////////////////////////////////////////////////////////////
  M [  0 ] = cw   + mcx2                                                     ;
  M [  1 ] = mcxy - swz                                                      ;
  M [  2 ] = mcxz + swy                                                      ;
  M [  3 ] = 0                                                               ;
  M [  4 ] = mcxy + swz                                                      ;
  M [  5 ] = cw   + mcy2                                                     ;
  M [  6 ] = mcyz - swx                                                      ;
  M [  7 ] = 0                                                               ;
  M [  8 ] = mcxz - swy                                                      ;
  M [  9 ] = mcyz + swx                                                      ;
  M [ 10 ] = cw   + mcz2                                                     ;
  M [ 11 ] = 0                                                               ;
  M [ 12 ] = 0                                                               ;
  M [ 13 ] = 0                                                               ;
  M [ 14 ] = 0                                                               ;
  M [ 15 ] = 1                                                               ;
  ////////////////////////////////////////////////////////////////////////////
  return (*this)                                                             ;
}

CA::Matrix4x4 CA::Matrix4x4::product(Matrix4x4 & v)
{
  Matrix4x4 P                    ;
  double  * A =     M            ;
  double  * R = P . M            ;
  double  * B = v . M            ;
  ////////////////////////////////
  R [  0 ] = A [  0 ] * B [  0 ] +
             A [  1 ] * B [  4 ] +
             A [  2 ] * B [  8 ] +
             A [  3 ] * B [ 12 ] ;
  R [  1 ] = A [  0 ] * B [  1 ] +
             A [  1 ] * B [  5 ] +
             A [  2 ] * B [  9 ] +
             A [  3 ] * B [ 13 ] ;
  R [  2 ] = A [  0 ] * B [  2 ] +
             A [  1 ] * B [  6 ] +
             A [  2 ] * B [ 10 ] +
             A [  3 ] * B [ 14 ] ;
  R [  3 ] = A [  0 ] * B [  3 ] +
             A [  1 ] * B [  7 ] +
             A [  2 ] * B [ 11 ] +
             A [  3 ] * B [ 15 ] ;
  ////////////////////////////////
  R [  4 ] = A [  4 ] * B [  0 ] +
             A [  5 ] * B [  4 ] +
             A [  6 ] * B [  8 ] +
             A [  7 ] * B [ 12 ] ;
  R [  5 ] = A [  4 ] * B [  1 ] +
             A [  5 ] * B [  5 ] +
             A [  6 ] * B [  9 ] +
             A [  7 ] * B [ 13 ] ;
  R [  6 ] = A [  4 ] * B [  2 ] +
             A [  5 ] * B [  6 ] +
             A [  6 ] * B [ 10 ] +
             A [  7 ] * B [ 14 ] ;
  R [  7 ] = A [  4 ] * B [  3 ] +
             A [  5 ] * B [  7 ] +
             A [  6 ] * B [ 11 ] +
             A [  7 ] * B [ 15 ] ;
  ////////////////////////////////
  R [  8 ] = A [  8 ] * B [  0 ] +
             A [  9 ] * B [  4 ] +
             A [ 10 ] * B [  8 ] +
             A [ 11 ] * B [ 12 ] ;
  R [  9 ] = A [  8 ] * B [  1 ] +
             A [  9 ] * B [  5 ] +
             A [ 10 ] * B [  9 ] +
             A [ 11 ] * B [ 13 ] ;
  R [ 10 ] = A [  8 ] * B [  2 ] +
             A [  9 ] * B [  6 ] +
             A [ 10 ] * B [ 10 ] +
             A [ 11 ] * B [ 14 ] ;
  R [ 11 ] = A [  8 ] * B [  3 ] +
             A [  9 ] * B [  7 ] +
             A [ 10 ] * B [ 11 ] +
             A [ 11 ] * B [ 15 ] ;
  ////////////////////////////////
  R [ 12 ] = A [ 12 ] * B [  0 ] +
             A [ 13 ] * B [  4 ] +
             A [ 14 ] * B [  8 ] +
             A [ 15 ] * B [ 12 ] ;
  R [ 13 ] = A [ 12 ] * B [  1 ] +
             A [ 13 ] * B [  5 ] +
             A [ 14 ] * B [  9 ] +
             A [ 15 ] * B [ 13 ] ;
  R [ 14 ] = A [ 12 ] * B [  2 ] +
             A [ 13 ] * B [  6 ] +
             A [ 14 ] * B [ 10 ] +
             A [ 15 ] * B [ 14 ] ;
  R [ 15 ] = A [ 12 ] * B [  3 ] +
             A [ 13 ] * B [  7 ] +
             A [ 14 ] * B [ 11 ] +
             A [ 15 ] * B [ 15 ] ;
  ////////////////////////////////
  return P                       ;
}

CA::Matrix4x4 CA::Matrix4x4::transpose(void)
{
  Matrix4x4 T             ;
  T . M [  0 ] = M [  0 ] ;
  T . M [  1 ] = M [  4 ] ;
  T . M [  2 ] = M [  8 ] ;
  T . M [  3 ] = M [ 12 ] ;
  /////////////////////////
  T . M [  4 ] = M [  1 ] ;
  T . M [  5 ] = M [  5 ] ;
  T . M [  6 ] = M [  9 ] ;
  T . M [  7 ] = M [ 13 ] ;
  /////////////////////////
  T . M [  8 ] = M [  2 ] ;
  T . M [  9 ] = M [  6 ] ;
  T . M [ 10 ] = M [ 10 ] ;
  T . M [ 11 ] = M [ 14 ] ;
  /////////////////////////
  T . M [ 12 ] = M [  3 ] ;
  T . M [ 13 ] = M [  7 ] ;
  T . M [ 14 ] = M [ 11 ] ;
  T . M [ 15 ] = M [ 15 ] ;
  return T                ;
}

#define MX(x,y) ( ( ( x - 1 ) * 4 ) + ( y - 1 ) )

// 1 1 =>  0 , 1 2 =>  1 , 1 3 =>  2 , 1 4 =>  3
// 2 1 =>  4 , 2 2 =>  5 , 2 3 =>  6 , 2 4 =>  7
// 3 1 =>  8 , 3 2 =>  9 , 3 3 => 10 , 3 4 => 11
// 4 1 => 12 , 4 2 => 13 , 4 3 => 14 , 4 4 => 15

bool CA::Matrix4x4::inverse(Matrix4x4 & T,double Z)
{
  double det    = 0                                                          ;
  double DET    = 0                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  double c11x22 = M [  0 ] * M [  5 ]                                        ;
  double c11x23 = M [  0 ] * M [  6 ]                                        ;
  double c11x24 = M [  0 ] * M [  7 ]                                        ;
  double c12x21 = M [  1 ] * M [  4 ]                                        ;
  double c12x23 = M [  1 ] * M [  6 ]                                        ;
  double c12x24 = M [  1 ] * M [  7 ]                                        ;
  double c13x21 = M [  2 ] * M [  4 ]                                        ;
  double c13x22 = M [  2 ] * M [  5 ]                                        ;
  double c13x24 = M [  2 ] * M [  7 ]                                        ;
  double c14x21 = M [  3 ] * M [  4 ]                                        ;
  double c14x22 = M [  3 ] * M [  5 ]                                        ;
  double c14x23 = M [  3 ] * M [  6 ]                                        ;
  ////////////////////////////////////////////////////////////////////////////
  double c32x41 = M [  9 ] * M [ 12 ]                                        ;
  double c33x41 = M [ 10 ] * M [ 12 ]                                        ;
  double c34x41 = M [ 11 ] * M [ 12 ]                                        ;
  double c31x42 = M [  8 ] * M [ 13 ]                                        ;
  double c33x42 = M [ 10 ] * M [ 13 ]                                        ;
  double c34x42 = M [ 11 ] * M [ 13 ]                                        ;
  double c31x43 = M [  8 ] * M [ 14 ]                                        ;
  double c32x43 = M [  9 ] * M [ 14 ]                                        ;
  double c34x43 = M [ 11 ] * M [ 14 ]                                        ;
  double c31x44 = M [  8 ] * M [ 15 ]                                        ;
  double c32x44 = M [  9 ] * M [ 15 ]                                        ;
  double c33x44 = M [ 10 ] * M [ 15 ]                                        ;
  ////////////////////////////////////////////////////////////////////////////
  det = ( c11x22 * c33x44 )                                                  +
        ( c11x23 * c34x42 )                                                  +
        ( c11x24 * c32x43 )                                                  +
        ( c12x21 * c34x43 )                                                  +
        ( c12x23 * c31x44 )                                                  +
        ( c12x24 * c33x41 )                                                  +
        ( c13x21 * c32x44 )                                                  +
        ( c13x22 * c34x41 )                                                  +
        ( c13x24 * c31x42 )                                                  +
        ( c14x21 * c33x42 )                                                  +
        ( c14x22 * c31x43 )                                                  +
        ( c14x23 * c32x41 )                                                  -
        ( c11x22 * c34x43 )                                                  -
        ( c11x23 * c32x44 )                                                  -
        ( c11x24 * c33x42 )                                                  -
        ( c12x21 * c33x44 )                                                  -
        ( c12x23 * c34x41 )                                                  -
        ( c12x24 * c31x43 )                                                  -
        ( c13x21 * c34x42 )                                                  -
        ( c13x22 * c31x44 )                                                  -
        ( c13x24 * c32x41 )                                                  -
        ( c14x21 * c32x43 )                                                  -
        ( c14x22 * c33x41 )                                                  -
        ( c14x23 * c31x42 )                                                  ;
  ////////////////////////////////////////////////////////////////////////////
  DET = det                                                                  ;
  if ( DET < 0 ) DET = -DET                                                  ;
  if ( DET < Z ) return false                                                ;
  DET = 1 / det                                                              ;
  ////////////////////////////////////////////////////////////////////////////
  T . M [  0 ] = ( M [  5 ] * c33x44 )                                       +
                 ( M [  6 ] * c34x42 )                                       +
                 ( M [  7 ] * c32x43 )                                       -
                 ( M [  5 ] * c34x43 )                                       -
                 ( M [  6 ] * c32x44 )                                       -
                 ( M [  7 ] * c33x42 )                                       ;
  T . M [  1 ] = ( M [  1 ] * c34x43 )                                       +
                 ( M [  2 ] * c32x44 )                                       +
                 ( M [  3 ] * c33x42 )                                       -
                 ( M [  1 ] * c33x44 )                                       -
                 ( M [  2 ] * c34x42 )                                       -
                 ( M [  3 ] * c32x43 )                                       ;
  T . M [  2 ] = ( M [ 15 ] * c12x23 )                                       +
                 ( M [ 13 ] * c13x24 )                                       +
                 ( M [ 14 ] * c14x22 )                                       -
                 ( M [ 14 ] * c12x24 )                                       -
                 ( M [ 15 ] * c13x22 )                                       -
                 ( M [ 13 ] * c14x23 )                                       ;
  T . M [  3 ] = ( M [ 10 ] * c12x24 )                                       +
                 ( M [ 11 ] * c13x22 )                                       +
                 ( M [  9 ] * c14x23 )                                       -
                 ( M [ 11 ] * c12x23 )                                       -
                 ( M [  9 ] * c13x24 )                                       -
                 ( M [ 10 ] * c14x22 )                                       ;
  ////////////////////////////////////////////////////////////////////////////
  T . M [  4 ] = ( M [  4 ] * c34x43 )                                       +
                 ( M [  6 ] * c31x44 )                                       +
                 ( M [  7 ] * c33x41 )                                       -
                 ( M [  4 ] * c33x44 )                                       -
                 ( M [  6 ] * c34x41 )                                       -
                 ( M [  7 ] * c31x43 )                                       ;
  T . M [  5 ] = ( M [  0 ] * c33x44 )                                       +
                 ( M [  2 ] * c34x41 )                                       +
                 ( M [  3 ] * c31x43 )                                       -
                 ( M [  0 ] * c34x43 )                                       -
                 ( M [  2 ] * c31x44 )                                       -
                 ( M [  3 ] * c33x41 )                                       ;
  T . M [  6 ] = ( M [ 14 ] * c11x24 )                                       +
                 ( M [ 15 ] * c13x21 )                                       +
                 ( M [ 12 ] * c14x23 )                                       -
                 ( M [ 15 ] * c11x23 )                                       -
                 ( M [ 12 ] * c13x24 )                                       -
                 ( M [ 14 ] * c14x21 )                                       ;
  T . M [  7 ] = ( M [ 11 ] * c11x23 )                                       +
                 ( M [  8 ] * c13x24 )                                       +
                 ( M [ 10 ] * c14x21 )                                       -
                 ( M [ 10 ] * c11x24 )                                       -
                 ( M [ 11 ] * c13x21 )                                       -
                 ( M [  8 ] * c14x23 )                                       ;
  ////////////////////////////////////////////////////////////////////////////
  T . M [  8 ] = ( M [  4 ] * c32x44 )                                       +
                 ( M [  5 ] * c34x41 )                                       +
                 ( M [  7 ] * c31x42 )                                       -
                 ( M [  4 ] * c34x42 )                                       -
                 ( M [  5 ] * c31x44 )                                       -
                 ( M [  7 ] * c32x41 )                                       ;
  T . M [  9 ] = ( M [  0 ] * c34x42 )                                       +
                 ( M [  1 ] * c31x44 )                                       +
                 ( M [  3 ] * c32x41 )                                       -
                 ( M [  0 ] * c32x44 )                                       -
                 ( M [  1 ] * c34x41 )                                       -
                 ( M [  3 ] * c31x42 )                                       ;
  T . M [ 10 ] = ( M [ 15 ] * c11x22 )                                       +
                 ( M [ 12 ] * c12x24 )                                       +
                 ( M [ 13 ] * c14x21 )                                       -
                 ( M [ 13 ] * c11x24 )                                       -
                 ( M [ 15 ] * c12x21 )                                       -
                 ( M [ 12 ] * c14x22 )                                       ;
  T . M [ 11 ] = ( M [  9 ] * c11x24 )                                       +
                 ( M [ 11 ] * c12x21 )                                       +
                 ( M [  8 ] * c14x22 )                                       -
                 ( M [ 11 ] * c11x22 )                                       -
                 ( M [  8 ] * c12x24 )                                       -
                 ( M [  9 ] * c14x21 )                                       ;
  ////////////////////////////////////////////////////////////////////////////
  T . M [ 12 ] = ( M [  4 ] * c33x42 )                                       +
                 ( M [  5 ] * c31x43 )                                       +
                 ( M [  6 ] * c32x41 )                                       -
                 ( M [  4 ] * c32x43 )                                       -
                 ( M [  5 ] * c33x41 )                                       -
                 ( M [  6 ] * c31x42 )                                       ;
  T . M [ 13 ] = ( M [  0 ] * c32x43 )                                       +
                 ( M [  1 ] * c33x41 )                                       +
                 ( M [  2 ] * c31x42 )                                       -
                 ( M [  0 ] * c33x42 )                                       -
                 ( M [  1 ] * c31x43 )                                       -
                 ( M [  2 ] * c32x41 )                                       ;
  T . M [ 14 ] = ( M [ 13 ] * c11x23 )                                       +
                 ( M [ 14 ] * c12x21 )                                       +
                 ( M [ 12 ] * c13x22 )                                       -
                 ( M [ 14 ] * c11x22 )                                       -
                 ( M [ 12 ] * c12x23 )                                       -
                 ( M [ 13 ] * c13x21 )                                       ;
  T . M [ 15 ] = ( M [ 10 ] * c11x22 )                                       +
                 ( M [  8 ] * c12x23 )                                       +
                 ( M [  9 ] * c13x21 )                                       -
                 ( M [  9 ] * c11x23 )                                       -
                 ( M [ 10 ] * c12x21 )                                       -
                 ( M [  8 ] * c13x22 )                                       ;
  ////////////////////////////////////////////////////////////////////////////
  for ( int i = 0 ; i < 16 ; i++ ) T . M [ i ] *= DET                        ;
  ////////////////////////////////////////////////////////////////////////////
  return true                                                                ;
}

CA::Vector4 CA::operator * (CA::Matrix4x4 & a,CA::Vector4 & b)
{
  Vector4  x                   ;
  double * R = x . values ( )  ;
  double * V = b . values ( )  ;
  double * M = a . values ( )  ;
  //////////////////////////////
  R [ 0 ] = V [ 0 ] * M [  0 ] +
            V [ 1 ] * M [  1 ] +
            V [ 2 ] * M [  2 ] +
            V [ 3 ] * M [  3 ] ;
  R [ 1 ] = V [ 0 ] * M [  4 ] +
            V [ 1 ] * M [  5 ] +
            V [ 2 ] * M [  6 ] +
            V [ 3 ] * M [  7 ] ;
  R [ 2 ] = V [ 0 ] * M [  8 ] +
            V [ 1 ] * M [  9 ] +
            V [ 2 ] * M [ 10 ] +
            V [ 3 ] * M [ 11 ] ;
  R [ 3 ] = V [ 0 ] * M [ 12 ] +
            V [ 1 ] * M [ 13 ] +
            V [ 2 ] * M [ 14 ] +
            V [ 3 ] * M [ 15 ] ;
  //////////////////////////////
  return x                     ;
}
