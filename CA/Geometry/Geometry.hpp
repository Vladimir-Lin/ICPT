#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <float.h>

#define FastCos cos
#define FastSin sin

class Ellipsoid
{
  public:

    explicit     Ellipsoid      (void) ;
                 Ellipsoid      (double R) ;
                 Ellipsoid      (double Ra,double Rb,double Rc) ;
                 Ellipsoid      (double Ra         ,
                                 double Rb         ,
                                 double Rc         ,
                                 int    longtitude ,
                                 int    latitude ) ;
    virtual     ~Ellipsoid      (void) ;

    int          longtitude     (void) const ;
    int          latitude       (void) const ;

    double     * Vertices       (void) ;
    double     * TexMappings    (void) ;

    virtual void setRadius      (double R) ;
    virtual void setRadius      (double Ra,double Rb,double Rc) ;

    virtual void setSegments    (int longtitude,int latitude) ;

    virtual void Generate       (void) ;

  protected:

    double   Ra         ;
    double   Rb         ;
    double   Rc         ;
    int      Longtitude ;
    int      Latitude   ;
    double * Points     ;
    double * Mappings   ;

  private:

    double * SinLambda  ;
    double * CosLambda  ;
    double * SinBeta    ;
    double * CosBeta    ;

    void         clearTables    (void) ;
    void         generateTables (void) ;

} ;

#endif // GEOMETRY_HPP
