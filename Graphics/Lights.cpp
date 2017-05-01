#include "Graphics.hpp"

CA::Lights:: Lights (void)
{
  MaxLights   = 8                               ;
  LocalViewer = false                           ;
  TwoSides    = false                           ;
  Ambient . setValues ( 0.2 , 0.2 , 0.2 , 1.0 ) ;
}

CA::Lights::~Lights (void)
{
  int  c = lights . count ( )                         ;
  bool b                                              ;
  for ( int i = 0 ; i < c ; i++ )                     {
    b = lights [ i ] -> isEnabled ( Light::DELETION ) ;
    if ( b ) delete lights [ i ]                      ;
  }                                                   ;
  lights . clear ( )                                  ;
}

int CA::Lights::addLight(Light * light)
{
  if ( NULL == light ) return lights . count ( ) ;
  lights << light                                ;
  return lights . count ( )                      ;
}

int CA::Lights::count(void)
{
  return lights . count ( ) ;
}

CA::Light * CA::Lights::Pos(int index)
{
  if ( index >= lights . count ( ) ) return NULL ;
  return lights [ index ]                        ;
}

void CA::Lights::takeLight (unsigned long long id)
{
  int     c = lights . count ( )             ;
  int     i = 0                              ;
  bool    b                                  ;
  Light * l                                  ;
  while ( i < c )                            {
    l = lights [ i ]                         ;
    if ( id == l -> Id ( ) )                 {
      lights . takeAt    ( i               ) ;
      b = l -> isEnabled ( Light::DELETION ) ;
      if ( b ) delete l                      ;
    } else                                   {
      i ++                                   ;
    }                                        ;
  }                                          ;
}

CA::Light * CA::Lights::At(unsigned long long id)
{
  int     c = lights . count ( ) ;
  int     i = 0                  ;
  Light * l                      ;
  while ( i < c )                {
    l = lights [ i ]             ;
    if ( id == l -> Id ( ) )     {
      return l                   ;
    } else                       {
      i ++                       ;
    }                            ;
  }                              ;
  return NULL                    ;
}

unsigned long long CA::Lights::MaxUuid(void)
{
  unsigned long long u = 0                  ;
  unsigned long long v                      ;
  int                c = lights . count ( ) ;
  for ( int i = 0 ; i < c ; i ++ )          {
    v = lights [ i ] -> Id ( )              ;
    if ( v > u ) u = v                      ;
  }                                         ;
  return u                                  ;
}

void CA::Lights::Prepare(void)
{
  ::glGetIntegerv ( GL_MAX_LIGHTS , & MaxLights ) ;
}

void CA::Lights::Enable(void)
{
  int  c = lights . count ( )                           ;
  bool b = false                                        ;
  for ( int i = 0 ; ( ! b ) && ( i < c ) ; i ++ )       {
    if ( lights [ i ] -> isEnabled ( Light::ACQUIRE ) ) {
      b = true                                          ;
    }                                                   ;
  }                                                     ;
  if ( b )                                              {
    ::glEnable    ( GL_LIGHTING )                       ;
      LightModels (             )                       ;
  } else                                                {
    ::glDisable   ( GL_LIGHTING )                       ;
  }                                                     ;
}

void CA::Lights::Disable(void)
{
  int c = lights . count ( )         ;
  for ( int i = 0 ; i < c ; i++ )    {
    lights [ i ] -> Disable  (    )  ;
    lights [ i ] -> setIndex ( -1 )  ;
  }                                  ;
  ::glDisable ( GL_LIGHTING )        ;
}

void CA::Lights::LightModels(void)
{
  GLfloat  F        [ 4 ]                               ;
  double * A = Ambient . values ( )                     ;
  ///////////////////////////////////////////////////////
  F [ 0 ] = A [ 0 ]                                     ;
  F [ 1 ] = A [ 1 ]                                     ;
  F [ 2 ] = A [ 2 ]                                     ;
  F [ 3 ] = A [ 3 ]                                     ;
  ///////////////////////////////////////////////////////
  ::glLightModelfv ( GL_LIGHT_MODEL_AMBIENT , F       ) ;
  ::glLightModeli  ( GL_LIGHT_MODEL_LOCAL_VIEWER        ,
                     LocalViewer ? GL_TRUE : GL_FALSE ) ;
  ::glLightModeli  ( GL_LIGHT_MODEL_TWO_SIDE            ,
                     TwoSides    ? GL_TRUE : GL_FALSE ) ;
}

void CA::Lights::Lighting(void)
{
  int c = lights . count ( )                              ;
  int p = 0                                               ;
  for ( int i = 0 ; i < c ; i++ )                         {
    if ( p < MaxLights )                                  {
      if ( lights [ i ] -> isEnabled ( Light::ACQUIRE ) ) {
        lights [ i ] -> setIndex ( p )                    ;
        lights [ i ] -> Execute  (   )                    ;
        p++                                               ;
      }                                                   ;
    }                                                     ;
  }                                                       ;
}

void CA::Lights::Execute(void)
{
  Enable   ( ) ;
  Lighting ( ) ;
}
