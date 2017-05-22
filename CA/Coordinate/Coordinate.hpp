#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include "Linear.hpp"

namespace CA
{

class Spherical
{
  public:

    explicit       Spherical   (void) ;
    virtual       ~Spherical   (void) ;

    static Vector4 toCartesian (Vector4 & s) ;
    static Vector4 toSpherical (Vector4 & c) ;

  protected:

  private:

} ;

}

#endif // COORDINATE_HPP
