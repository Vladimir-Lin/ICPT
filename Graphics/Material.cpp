#include "Graphics.hpp"

CA::Material:: Material(void)
{
  uuid            =  0                                ;
  name            = ""                                ;
  /////////////////////////////////////////////////////
  Booleans  [ 0 ] = false                             ;
  Booleans  [ 1 ] = false                             ;
  Booleans  [ 2 ] = false                             ;
  Booleans  [ 3 ] = false                             ;
  Booleans  [ 4 ] = false                             ;
  Booleans  [ 5 ] = true                              ;
  /////////////////////////////////////////////////////
  Faces     [ 0 ] = GL_FRONT_AND_BACK                 ;
  Faces     [ 1 ] = GL_FRONT_AND_BACK                 ;
  Faces     [ 2 ] = GL_FRONT_AND_BACK                 ;
  Faces     [ 3 ] = GL_FRONT_AND_BACK                 ;
  Faces     [ 4 ] = GL_FRONT_AND_BACK                 ;
  /////////////////////////////////////////////////////
  Ambient   . setValues ( 0.20 , 0.20 , 0.20 , 1.00 ) ;
  Diffuse   . setValues ( 0.80 , 0.80 , 0.80 , 1.00 ) ;
  Specular  . setValues ( 0.00 , 0.00 , 0.00 , 1.00 ) ;
  Shininess . setValues ( 0.00 , 0.00 , 0.00 , 1.00 ) ;
  Emission  . setValues ( 0.00 , 0.00 , 0.00 , 1.00 ) ;
}

CA::Material::~Material(void)
{
}

unsigned long long CA::Material::Id(void)
{
  return uuid ;
}

void CA::Material::setId(unsigned long long id)
{
  uuid = id ;
}

QString CA::Material::Name(void) const
{
  return name ;
}

void CA::Material::setName(QString N)
{
  name = N ;
}

int CA::Material::Face(int index) const
{
  return Faces [ index ] ;
}

void CA::Material::setFace(int index,int face)
{
  Faces [ index ] = face ;
}

CA::Vector4 & CA::Material::Data(int index)
{
  switch ( index )                    {
    case AMBIENT   : return Ambient   ;
    case DIFFUSE   : return Diffuse   ;
    case SPECULAR  : return Specular  ;
    case SHININESS : return Shininess ;
    case EMISSION  : return Emission  ;
  }                                   ;
  return Vector4 ( )                  ;
}

CA::Vector4 & CA::Material::setData(int index,double v1,double v2,double v3,double v4)
{
  Data ( index ) . setValues ( v1 , v2 , v3 , v4 ) ;
  return Data ( index )                            ;
}

bool CA::Material::isEnabled(int index) const
{
  switch ( index )                         {
    case AMBIENT   : return Booleans [ 0 ] ;
    case DIFFUSE   : return Booleans [ 1 ] ;
    case SPECULAR  : return Booleans [ 2 ] ;
    case SHININESS : return Booleans [ 3 ] ;
    case EMISSION  : return Booleans [ 4 ] ;
    case ENABLING  : return Booleans [ 5 ] ;
  }                                        ;
  return false                             ;
}

bool CA::Material::setEnabled(int index,bool enabled)
{
  switch ( index )             {
    case AMBIENT               :
      Booleans [ 0 ] = enabled ;
    break                      ;
    case DIFFUSE               :
      Booleans [ 1 ] = enabled ;
    break                      ;
    case SPECULAR              :
      Booleans [ 2 ] = enabled ;
    break                      ;
    case SHININESS             :
      Booleans [ 3 ] = enabled ;
    break                      ;
    case EMISSION              :
      Booleans [ 4 ] = enabled ;
    break                      ;
    case ENABLING              :
      Booleans [ 5 ] = enabled ;
    break                      ;
  }                            ;
  return               enabled ;
}

void CA::Material::Materialfv (
       GLenum    face         ,
       GLenum    pname        ,
       Vector4 & P            )
{
  GLfloat   F [ 4 ]                   ;
  double *  p = P . values ( )        ;
  /////////////////////////////////////
  F [ 0 ] = p [ 0 ]                   ;
  F [ 1 ] = p [ 1 ]                   ;
  F [ 2 ] = p [ 2 ]                   ;
  F [ 3 ] = p [ 3 ]                   ;
  /////////////////////////////////////
  ::glMaterialfv ( face , pname , F ) ;
}

void CA::Material::Execute(void)
{
  if ( ! Booleans [ 5 ] ) return                             ;
  if (   Booleans [ 0 ] )                                    {
    Materialfv    ( Faces [ 0 ] , GL_AMBIENT   , Ambient   ) ;
  }                                                          ;
  if (   Booleans [ 1 ] )                                    {
    Materialfv    ( Faces [ 1 ] , GL_DIFFUSE   , Diffuse   ) ;
  }                                                          ;
  if (   Booleans [ 2 ] )                                    {
    Materialfv    ( Faces [ 2 ] , GL_SPECULAR  , Specular  ) ;
  }                                                          ;
  if (   Booleans [ 3 ] )                                    {
    Materialfv    ( Faces [ 3 ] , GL_SHININESS , Shininess ) ;
  }                                                          ;
  if (   Booleans [ 4 ] )                                    {
    Materialfv    ( Faces [ 4 ] , GL_EMISSION  , Emission  ) ;
  }                                                          ;
}
