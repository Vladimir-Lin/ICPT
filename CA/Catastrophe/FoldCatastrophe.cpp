#include "Catastrophe.hpp"

CA::Catastrophe::Fold:: Fold (void)
{
}

CA::Catastrophe::Fold:: Fold (double a,double b,double c)
{
  setParameters ( a , b , c ) ;
}

CA::Catastrophe::Fold::~Fold (void)
{
}

void CA::Catastrophe::Fold::setParameters(double a,double b,double c)
{
  A    = a     ;
  B    = b     ;
  C    = c     ;
  z    = b     ;
  if ( a > 0 ) {
    z /= a     ;
  } else
  if ( a < 0 ) {
    z /= a     ;
  }            ;
  a3   = a * 3 ;
  a6   = a * 6 ;
}

double CA::Catastrophe::Fold::Z(void) const
{
  return z ;
}

bool CA::Catastrophe::Fold::Unstable(void)
{
  return   ( z > 0 ) ;
}

bool CA::Catastrophe::Fold::Stable(void)
{
  return ! ( z > 0 ) ;
}

void CA::Catastrophe::Fold::setX(double x)
{
  X  = x      ;
  X2 = x  * x ; // x ^ 2
  X3 = X2 * x ; // x ^ 3
}

double CA::Catastrophe::Fold::OnlyV(double x)
{
  setX         ( x ) ;
  return OnlyV (   ) ;
}

double CA::Catastrophe::Fold::OnlyV(void)
{
  v   =   C         ;
  v  += ( B  * X  ) ;
  v  += ( A  * X3 ) ;
  return v          ;
}

void CA::Catastrophe::Fold::CalculateX(double x)
{
  setX  ( x       ) ;
  ///////////////////
  v   =   C         ;
  v  += ( B  * X  ) ;
  v  += ( A  * X3 ) ;
  y   =   v  / A    ;
  ///////////////////
  vp  =   B         ;
  vp += ( a3 * X2 ) ;
  yp  =   vp / A    ;
  ///////////////////
  vpp =   a6 * X    ;
  ypp =    6 * X    ;
}

double CA::Catastrophe::Fold::CalculateV(void)
{
  v   =   C        ;
  v  += ( B * X  ) ;
  v  += ( A * X3 ) ;
  y   =   v / A    ;
  return v         ;
}

double CA::Catastrophe::Fold::CalculateVp(void)
{
  vp  =   B         ;
  vp += ( a3 * X2 ) ;
  yp  =   vp / A    ;
  return vp         ;
}

double CA::Catastrophe::Fold::CalculateVpp(void)
{
  vpp = a6 * X ;
  ypp =  6 * X ;
  return vpp   ;
}

double CA::Catastrophe::Fold::V(void)
{
  return v ;
}

double CA::Catastrophe::Fold::Vp(void)
{
  return vp ;
}

double CA::Catastrophe::Fold::Vpp(void)
{
  return vpp ;
}

double CA::Catastrophe::Fold::Y(void)
{
  return y ;
}

double CA::Catastrophe::Fold::Yp(void)
{
  return yp ;
}

double CA::Catastrophe::Fold::Ypp(void)
{
  return ypp ;
}
