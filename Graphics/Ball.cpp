#include "Graphics.hpp"

CA::Ball:: Ball      ( void )
         : Ellipsoid (      )
{
  texture  = NULL ;
}

CA::Ball::~Ball (void)
{
  delete texture ;
}

void CA::Ball::PushPoints(int n,int gaps,double * points)
{
  for ( int i = 0 , p = 0 ; i < n ; i++ , p += gaps ) {
    ::glVertex3dv ( & points [ p ] )                  ;
  }                                                   ;
}

bool CA::Ball::loadTexture (QString res)
{
  if ( NULL == texture ) texture = new Texture ( ) ;
  return texture -> loadResource ( res )           ;
}

void CA::Ball::DrawLongtitude(int x,int y)
{
  double * point = Points                              ;
  int      n     = Longtitude                          ;
  int      m     = Latitude                            ;
  int      X     = n / x                               ;
  int      n3    = n * 3                               ;
  //////////////////////////////////////////////////////
  for ( int i = 0 ; i < x ; i++ )                      {
    int w = i * X * 3                                  ;
    ::glBegin   ( GL_LINE_STRIP                      ) ;
    PushPoints  ( ( 2 * m + 1 ) , n3 , & point [ w ] ) ;
    ::glEnd     (                                    ) ;
  }                                                    ;
}

void CA::Ball::DrawLatitude(int x,int y)
{
  double * point = Points                              ;
  int      n     = Longtitude                          ;
  int      m     = Latitude                            ;
  int      Y     = m / y                               ;
  int      n3    = n * 3                               ;
  int      y2    = y * 2                               ;
  //////////////////////////////////////////////////////
  for ( int j = 1 ; j < y2 ; j ++ )                    {
    int p = j * Y * n3                                 ;
    ::glBegin   ( GL_LINE_LOOP                       ) ;
    PushPoints  ( n , 3 , & point [ p ]              ) ;
    ::glEnd     (                                    ) ;
  }                                                    ;
}

void CA::Ball::DrawWire(int x,int y)
{
  double * point = Points                              ;
  int      n     = Longtitude                          ;
  int      m     = Latitude                            ;
  int      X     = n / x                               ;
  int      Y     = m / y                               ;
  int      n3    = n * 3                               ;
  int      y2    = y * 2                               ;
  //////////////////////////////////////////////////////
  for ( int i = 0 ; i < x ; i++ )                      {
    int w = i * X * 3                                  ;
    ::glBegin   ( GL_LINE_STRIP                      ) ;
    PushPoints  ( ( 2 * m + 1 ) , n3 , & point [ w ] ) ;
    ::glEnd     (                                    ) ;
  }                                                    ;
  //////////////////////////////////////////////////////
  for ( int j = 1 ; j < y2 ; j ++ )                    {
    int p = j * Y * n3                                 ;
    ::glBegin   ( GL_LINE_LOOP                       ) ;
    PushPoints  ( n , 3 , & point [ p ]              ) ;
    ::glEnd     (                                    ) ;
  }                                                    ;
}

void CA::Ball::Surface(void)
{
  int n = Longtitude                                                         ;
  int m = Latitude                                                           ;
  ////////////////////////////////////////////////////////////////////////////
  ::glBegin             ( GL_QUADS                                         ) ;
  ////////////////////////////////////////////////////////////////////////////
  int n1 = n + 1                                                             ;
  for   ( int j = - m ; j < m ; j ++ )                                       {
    int p1 = m  + j                                                          ;
    int p2 = p1 + 1                                                          ;
    int s1 = n  * p1 * 3                                                     ;
    int s2 = n  * p2 * 3                                                     ;
    int t1 = n1 * p1 * 2                                                     ;
    int t2 = n1 * p2 * 2                                                     ;
    for ( int i = 0 ; i < n ; i ++ )                                         {
      int z  = i + 1                                                         ;
      int w  = z % n                                                         ;
      int i3 = i * 3                                                         ;
      int z3 = w * 3                                                         ;
      int i2 = i * 2                                                         ;
      int z2 = z * 2                                                         ;
      int ps [ 4 ]                                                           ;
      int pt [ 4 ]                                                           ;
      ////////////////////////////////////////////////////////////////////////
      ps [ 0 ] = s1 + i3                                                     ;
      ps [ 1 ] = s1 + z3                                                     ;
      ps [ 2 ] = s2 + z3                                                     ;
      ps [ 3 ] = s2 + i3                                                     ;
      ////////////////////////////////////////////////////////////////////////
      pt [ 0 ] = t1 + i2                                                     ;
      pt [ 1 ] = t1 + z2                                                     ;
      pt [ 2 ] = t2 + z2                                                     ;
      pt [ 3 ] = t2 + i2                                                     ;
      ////////////////////////////////////////////////////////////////////////
      for ( int w = 0 ; w < 4 ; w++ )                                        {
        ::glVertex3dv   ( & Points   [ ps [ w ] ]                          ) ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  ::glEnd               (                                                  ) ;
}

void CA::Ball::Render(void)
{
  int n = Longtitude                                                         ;
  int m = Latitude                                                           ;
  ////////////////////////////////////////////////////////////////////////////
  ::glEnable            ( GL_TEXTURE_2D                                    ) ;
  if ( NULL != texture )                                                     {
    texture -> Bind     (                                                  ) ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  ::glBegin             ( GL_QUADS                                         ) ;
  ////////////////////////////////////////////////////////////////////////////
  int n1 = n + 1                                                             ;
  for   ( int j = - m ; j < m ; j ++ )                                       {
    int p1 = m  + j                                                          ;
    int p2 = p1 + 1                                                          ;
    int s1 = n  * p1 * 3                                                     ;
    int s2 = n  * p2 * 3                                                     ;
    int t1 = n1 * p1 * 2                                                     ;
    int t2 = n1 * p2 * 2                                                     ;
    for ( int i = 0 ; i < n ; i ++ )                                         {
      int z  = i + 1                                                         ;
      int w  = z % n                                                         ;
      int i3 = i * 3                                                         ;
      int z3 = w * 3                                                         ;
      int i2 = i * 2                                                         ;
      int z2 = z * 2                                                         ;
      int ps [ 4 ]                                                           ;
      int pt [ 4 ]                                                           ;
      ////////////////////////////////////////////////////////////////////////
      ps [ 0 ] = s1 + i3                                                     ;
      ps [ 1 ] = s1 + z3                                                     ;
      ps [ 2 ] = s2 + z3                                                     ;
      ps [ 3 ] = s2 + i3                                                     ;
      ////////////////////////////////////////////////////////////////////////
      pt [ 0 ] = t1 + i2                                                     ;
      pt [ 1 ] = t1 + z2                                                     ;
      pt [ 2 ] = t2 + z2                                                     ;
      pt [ 3 ] = t2 + i2                                                     ;
      ////////////////////////////////////////////////////////////////////////
      for ( int w = 0 ; w < 4 ; w++ )                                        {
        ::glTexCoord2dv ( & Mappings [ pt [ w ] ] )                          ;
        ::glVertex3dv   ( & Points   [ ps [ w ] ] )                          ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  ::glEnd               (                                                  ) ;
  ////////////////////////////////////////////////////////////////////////////
  if ( NULL != texture )                                                     {
    texture -> Release  (                                                  ) ;
  }                                                                          ;
  ::glDisable           ( GL_TEXTURE_2D                                    ) ;
}
