#ifndef CATASTROPHE_HPP
#define CATASTROPHE_HPP

namespace CA
{

namespace Catastrophe {

// Fold Catastrophe
// Y  = (     a * ( X ^ 3 ) ) + ( b x ) + c
// Y' = ( 3 * a * ( X ^ 2 ) ) +   b
// Y" =   6 * a *   X
// z  = b / a
// x for X axis
// y for Y axis
// z for Z axis , z > 0 has no meaning actually

class Fold
{
  public:

    explicit Fold          (void) ;
    explicit Fold          (double a,double b,double c = 0) ;
    virtual ~Fold          (void) ;

    void     setParameters (double a,double b,double c = 0) ;

    bool     Unstable      (void) ;
    bool     Stable        (void) ;

    void     setX          (double x) ;
    void     CalculateX    (double x) ;

    double   Z             (void) const ;

    double   OnlyV         (double x) ;
    double   OnlyV         (void) ;

    double   CalculateV    (void) ;
    double   CalculateVp   (void) ;
    double   CalculateVpp  (void) ;

    double   V             (void) ;
    double   Vp            (void) ;
    double   Vpp           (void) ;

    double   Y             (void) ;
    double   Yp            (void) ;
    double   Ypp           (void) ;

  protected:

    double A   ;
    double B   ;
    double C   ;
    double z   ;
    double a3  ;
    double a6  ;
    double X   ;
    double X2  ;
    double X3  ;
    double v   ;
    double vp  ;
    double vpp ;
    double y   ;
    double yp  ;
    double ypp ;

  private:

} ;

}

}

#endif // CATASTROPHE_HPP
