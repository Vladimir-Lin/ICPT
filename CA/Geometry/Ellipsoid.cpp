#include "Geometry.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

Ellipsoid:: Ellipsoid  ( void )
          : Ra         ( 0    )
          , Rb         ( 0    )
          , Rc         ( 0    )
          , Longtitude ( 0    )
          , Latitude   ( 0    )
          , Points     ( NULL )
          , Mappings   ( NULL )
          , SinLambda  ( NULL )
          , CosLambda  ( NULL )
          , SinBeta    ( NULL )
          , CosBeta    ( NULL )
{
}

Ellipsoid:: Ellipsoid  ( double R )
          : Ra         ( R        )
          , Rb         ( R        )
          , Rc         ( R        )
          , Longtitude ( 0        )
          , Latitude   ( 0        )
          , Points     ( NULL     )
          , Mappings   ( NULL     )
          , SinLambda  ( NULL     )
          , CosLambda  ( NULL     )
          , SinBeta    ( NULL     )
          , CosBeta    ( NULL     )
{
}

Ellipsoid:: Ellipsoid  ( double ra ,
                         double rb ,
                         double rc )
          : Ra         ( ra        )
          , Rb         ( rb        )
          , Rc         ( rc        )
          , Longtitude ( 0         )
          , Latitude   ( 0         )
          , Points     ( NULL      )
          , Mappings   ( NULL      )
          , SinLambda  ( NULL      )
          , CosLambda  ( NULL      )
          , SinBeta    ( NULL      )
          , CosBeta    ( NULL      )
{
}

Ellipsoid:: Ellipsoid  ( double ra         ,
                         double rb         ,
                         double rc         ,
                         int    longtitude ,
                         int    latitude   )
          : Ra         ( ra                )
          , Rb         ( rb                )
          , Rc         ( rc                )
          , Longtitude ( longtitude        )
          , Latitude   ( latitude          )
          , Points     ( NULL              )
          , Mappings   ( NULL              )
          , SinLambda  ( NULL              )
          , CosLambda  ( NULL              )
          , SinBeta    ( NULL              )
          , CosBeta    ( NULL              )
{
}

Ellipsoid::~Ellipsoid(void)
{
  if ( NULL != Points   ) {
    delete [ ] Points     ;
  }                       ;
  if ( NULL != Mappings ) {
    delete [ ] Mappings   ;
  }                       ;
  Points   = NULL         ;
  Mappings = NULL         ;
  clearTables ( )         ;
}

int Ellipsoid::longtitude(void) const
{
  return Longtitude ;
}

int Ellipsoid::latitude(void) const
{
  return Latitude ;
}

double * Ellipsoid::Vertices(void)
{
  return Points ;
}

double * Ellipsoid::TexMappings(void)
{
  return Mappings ;
}

void Ellipsoid::clearTables(void)
{
  if ( NULL != SinLambda ) {
    delete [ ] SinLambda   ;
  }                        ;
  if ( NULL != CosLambda ) {
    delete [ ] CosLambda   ;
  }                        ;
  if ( NULL != SinBeta   ) {
    delete [ ] SinBeta     ;
  }                        ;
  if ( NULL != CosBeta   ) {
    delete [ ] CosBeta     ;
  }                        ;
  //////////////////////////
  SinLambda = NULL         ;
  CosLambda = NULL         ;
  SinBeta   = NULL         ;
  CosBeta   = NULL         ;
}

void Ellipsoid::generateTables(void)
{
  int    n        = Longtitude + 1       ;
  int    m        = Latitude             ;
  int    L        = m + m      + 1       ;
  double piLambda = M_PI * 2 /   n       ;
  double piBeta   = M_PI     / ( m * 2 ) ;
  ////////////////////////////////////////
  SinLambda = new double [ n ]           ;
  CosLambda = new double [ n ]           ;
  SinBeta   = new double [ L ]           ;
  CosBeta   = new double [ L ]           ;
  ////////////////////////////////////////
  for   ( int j = - m ; j <= m ; j ++ )  {
    double Beta = piBeta * j             ;
    int    p    = m      + j             ;
    //////////////////////////////////////
    SinBeta   [ p ] = FastSin ( Beta   ) ;
    CosBeta   [ p ] = FastCos ( Beta   ) ;
    //////////////////////////////////////
  }                                      ;
  ////////////////////////////////////////
  for ( int i =   0 ; i <  n ; i ++ )    {
    double Lambda = piLambda * i         ;
    //////////////////////////////////////
    SinLambda [ i ] = FastSin ( Lambda ) ;
    CosLambda [ i ] = FastCos ( Lambda ) ;
    //////////////////////////////////////
  }                                      ;
}

void Ellipsoid::setRadius(double R)
{
  Ra = R ;
  Rb = R ;
  Rc = R ;
}

void Ellipsoid::setRadius(double ra,double rb,double rc)
{
  Ra = ra ;
  Rb = rb ;
  Rc = rc ;
}

void Ellipsoid::setSegments(int longtitude,int latitude)
{
  Longtitude = longtitude ;
  Latitude   = latitude   ;
}

void Ellipsoid::Generate(void)
{
  if ( 0 >= Longtitude ) return                                             ;
  if ( 0 >= Latitude   ) return                                             ;
  ///////////////////////////////////////////////////////////////////////////
  generateTables ( )                                                        ;
  ///////////////////////////////////////////////////////////////////////////
  int n          = Longtitude                                               ;
  int m          = Latitude                                                 ;
  int m2         = m + m                                                    ;
  int n1         = n + 1                                                    ;
  int longtitude = m + m + 1                                                ;
  int v3         = n  * longtitude * 3                                      ;
  int v2         = n1 * longtitude * 2                                      ;
  ///////////////////////////////////////////////////////////////////////////
  if ( NULL != Points   ) delete [ ] Points                                 ;
  if ( NULL != Mappings ) delete [ ] Mappings                               ;
  ///////////////////////////////////////////////////////////////////////////
  Points   = new double [ v3 ]                                              ;
  Mappings = new double [ v2 ]                                              ;
  ///////////////////////////////////////////////////////////////////////////
  for   ( int j = - m ; j <= m ; j ++ )                                     {
    int    p  = m  + j                                                      ;
    int    p2 = p  + p                                                      ;
    int    p3 = p2 + p                                                      ;
    int    s  = n  * p3                                                     ;
    int    t  = n1 * p2                                                     ;
    double RC = Rc * SinBeta [ p ]                                          ;
    double lt = 1 - ( ( double ) ( j + m ) / m2 )                           ; // reverse ?
    for ( int i = 0 , i2 = 0 , i3 = 0 ; i <= n ; i ++ , i2 += 2 , i3 += 3 ) {
      int    ps = s + i3                                                    ;
      int    pt = t + i2                                                    ;
      double mx = i                                                         ;
      mx /= n                                                               ;
      ///////////////////////////////////////////////////////////////////////
      if ( i < n )                                                          {
        Points [ ps     ] = Ra * CosBeta [ p ] * CosLambda [ i ]            ;
        Points [ ps + 1 ] = Rb * CosBeta [ p ] * SinLambda [ i ]            ;
        Points [ ps + 2 ] = RC                                              ;
      }                                                                     ;
      ///////////////////////////////////////////////////////////////////////
      Mappings [ pt     ] = mx                                              ;
      Mappings [ pt + 1 ] = lt                                              ;
      ///////////////////////////////////////////////////////////////////////
    }                                                                       ;
  }                                                                         ;
  ///////////////////////////////////////////////////////////////////////////
  clearTables    ( )                                                        ;
}
