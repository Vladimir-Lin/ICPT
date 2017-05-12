#include "Graphics.hpp"

CA::Position:: Position (void)
{
}

CA::Position::~Position (void)
{
}

void CA::Position::Push(void)
{
  double * t = T . values ( )                              ;
  double * r = R . values ( )                              ;
  double * a = A . values ( )                              ;
  double * s = S . values ( )                              ;
  //////////////////////////////////////////////////////////
  ::glPushMatrix (                                       ) ;
  //////////////////////////////////////////////////////////
  ::glTranslated (           t [ 0 ] , t [ 1 ] , t [ 2 ] ) ;
  ::glRotated    ( a [ 3 ] , a [ 0 ] , a [ 1 ] , a [ 2 ] ) ;
  ::glRotated    ( r [ 3 ] , r [ 0 ] , r [ 1 ] , r [ 2 ] ) ;
  ::glScaled     (           s [ 0 ] , s [ 1 ] , s [ 2 ] ) ;
}

void CA::Position::Pop(void)
{
  ::glPopMatrix ( ) ;
}
