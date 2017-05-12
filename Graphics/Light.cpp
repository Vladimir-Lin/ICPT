#include "Graphics.hpp"

CA::Light:: Light (void)
{
  uuid           =  0                                  ;
  name           = ""                                  ;
  Index          = -1                                  ;
  //////////////////////////////////////////////////////
  Booleans [ 0 ] = true                                ;
  Booleans [ 1 ] = true                                ;
  Booleans [ 2 ] = false                               ;
  Booleans [ 3 ] = false                               ;
  Booleans [ 4 ] = true                                ;
  //////////////////////////////////////////////////////
  Position    . setValues (   0.0 , 0.0 ,  0.0 , 0.0 ) ;
  Direction   . setValues (   0.0 , 0.0 , -1.0 , 0.0 ) ;
  SpotAt      . setValues (   0.0 , 0.0 ,  1.0 , 0.0 ) ;
  Ambient     . setValues (   0.0 , 0.0 ,  0.0 , 1.0 ) ;
  Diffuse     . setValues (   1.0 , 1.0 ,  1.0 , 1.0 ) ;
  Specular    . setValues (   1.0 , 1.0 ,  1.0 , 1.0 ) ;
  CutOff      . setValues ( 180.0 , 0.0 ,  0.0 , 1.0 ) ;
  Attenuation . setValues (   1.0 , 0.0 ,  0.0 , 0.0 ) ;
  DA          . setValues (   0.0 , 0.0 ,  0.0 , 1.0 ) ;
  DDS         . setValues (   1.0 , 1.0 ,  1.0 , 1.0 ) ;
}

CA::Light::~Light (void)
{
}

unsigned long long CA::Light::Id(void)
{
  return uuid ;
}

void CA::Light::setId(unsigned long long id)
{
  uuid = id ;
}

QString CA::Light::Name(void) const
{
  return name ;
}

void CA::Light::setName(QString N)
{
  name = N ;
}

bool CA::Light::isEnabled(void) const
{
  return ( Index >= 0 ) ;
}

bool CA::Light::isEnabled(int index) const
{
  switch ( index )                           {
    case ACQUIRE     : return Booleans [ 0 ] ;
    case COLORS      : return Booleans [ 1 ] ;
    case SPOT        : return Booleans [ 2 ] ;
    case ATTENUATION : return Booleans [ 3 ] ;
    case DELETION    : return Booleans [ 4 ] ;
  }                                          ;
  return false                               ;
}

bool CA::Light::setEnabled(int index,bool enabled)
{
  switch ( index )             {
    case ACQUIRE               :
      Booleans [ 0 ] = enabled ;
    break                      ;
    case COLORS                :
      Booleans [ 1 ] = enabled ;
    break                      ;
    case SPOT                  :
      Booleans [ 2 ] = enabled ;
    break                      ;
    case ATTENUATION           :
      Booleans [ 3 ] = enabled ;
    break                      ;
    case DELETION              :
      Booleans [ 4 ] = enabled ;
    break                      ;
  }                            ;
  return               enabled ;
}

int CA::Light::LightIndex(void) const
{
  return GL_LIGHT0 + Index ;
}

void CA::Light::setIndex(int index)
{
  Index = index ;
}

void CA::Light::Enable(void)
{
  if ( Index < 0 ) return        ;
  ::glEnable  ( LightIndex ( ) ) ;
}

void CA::Light::Disable(void)
{
  if ( Index < 0 ) return        ;
  ::glDisable ( LightIndex ( ) ) ;
}

CA::Vector4 & CA::Light::Data(int index)
{
  switch ( index )                        {
    case POSITION    : return Position    ;
    case SPOT        : return Direction   ;
    case SPOTAT      : return SpotAt      ;
    case AMBIENT     : return Ambient     ;
    case DIFFUSE     : return Diffuse     ;
    case SPECULAR    : return Specular    ;
    case CUTOFF      : return CutOff      ;
    case ATTENUATION : return Attenuation ;
  }                                       ;
  return Vector4 ( )                      ;
}

CA::Vector4 & CA::Light::setData(int index,double v1,double v2,double v3,double v4)
{
  Data ( index ) . setValues ( v1 , v2 , v3 , v4 ) ;
  return Data ( index )                            ;
}

void CA::Light::Lightfv(GLenum light,GLenum pname,Vector4 & p)
{
  GLfloat  F  [ 4 ]                 ;
  double * P = p . values ( )       ;
  F [ 0 ] = P [ 0 ]                 ;
  F [ 1 ] = P [ 1 ]                 ;
  F [ 2 ] = P [ 2 ]                 ;
  F [ 3 ] = P [ 3 ]                 ;
  ::glLightfv ( light , pname , F ) ;
}

void CA::Light::AssignPosition(void)
{
  if ( Index < 0 ) return                             ;
  Lightfv ( LightIndex ( ) , GL_POSITION , Position ) ;
}

void CA::Light::AssignColors(void)
{
  if ( Index < 0      ) return                 ;
  int index = LightIndex ( )                   ;
  if ( Booleans [ 1 ] )                        {
    Lightfv ( index , GL_AMBIENT  , Ambient  ) ;
    Lightfv ( index , GL_DIFFUSE  , Diffuse  ) ;
    Lightfv ( index , GL_SPECULAR , Specular ) ;
  } else                                       {
    Lightfv ( index , GL_AMBIENT  , DA       ) ;
    Lightfv ( index , GL_DIFFUSE  , DDS      ) ;
    Lightfv ( index , GL_SPECULAR , DDS      ) ;
  }                                            ;
}

void CA::Light::AssignSpots(void)
{
  if ( Index < 0      ) return                           ;
  int index = LightIndex ( )                             ;
  if ( Booleans [ 2 ] )                                  {
    double * C = CutOff . values ( )                     ;
    Direction = SpotAt - Position                        ;
    Lightfv    ( index , GL_SPOT_DIRECTION , Direction ) ;
    ::glLightf ( index , GL_SPOT_CUTOFF    , C [ 0 ]   ) ;
    ::glLightf ( index , GL_SPOT_EXPONENT  , C [ 1 ]   ) ;
  } else                                                 {
    ::glLightf ( index , GL_SPOT_CUTOFF    , 180.0     ) ;
  }                                                      ;
}

void CA::Light::AssignAttenuation(void)
{
  if ( Index < 0      ) return                                ;
  int index = LightIndex ( )                                  ;
  if ( Booleans [ 3 ] )                                       {
    double * A = Attenuation . values ( )                     ;
    ::glLightf ( index , GL_CONSTANT_ATTENUATION  , A [ 0 ] ) ;
    ::glLightf ( index , GL_LINEAR_ATTENUATION    , A [ 1 ] ) ;
    ::glLightf ( index , GL_QUADRATIC_ATTENUATION , A [ 2 ] ) ;
  } else                                                      {
    ::glLightf ( index , GL_CONSTANT_ATTENUATION  , 1.0     ) ;
    ::glLightf ( index , GL_LINEAR_ATTENUATION    , 0.0     ) ;
    ::glLightf ( index , GL_QUADRATIC_ATTENUATION , 0.0     ) ;
  }                                                           ;
}

void CA::Light::Execute(void)
{
  Enable            ( ) ;
  AssignPosition    ( ) ;
  AssignColors      ( ) ;
  AssignSpots       ( ) ;
  AssignAttenuation ( ) ;
}
