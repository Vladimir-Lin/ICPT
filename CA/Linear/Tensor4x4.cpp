#include "Linear.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

CA::Tensor4x4:: Tensor4x4 (void)
{
}

CA::Tensor4x4::~Tensor4x4 (void)
{
}

double * CA::Tensor4x4::values(void)
{
  return T ;
}
