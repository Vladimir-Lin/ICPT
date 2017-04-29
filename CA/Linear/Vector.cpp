#include <stdio.h>
#include <stdlib.h>

#include "Linear.hpp"

CA::Vector:: Vector ( int items )
           : V      ( NULL      )
           , P      ( NULL      )
{
  allocate ( items ) ;
}

CA::Vector:: Vector ( double * address )
           : V      (          address )
           , P      ( NULL             )
{
}

CA::Vector::~Vector(void)
{
  if ( NULL != P ) {
    delete [ ] P   ;
    V = NULL       ;
    P = NULL       ;
  }                ;
}

int CA::Vector::type(void) const
{
  return 0 ;
}

void CA::Vector::allocate(int items)
{
  if ( NULL != P ) delete [ ] P ;
  V = new double [ items ]      ;
  P = V                         ;
}
