#include "Graphics.hpp"

CA::Texture:: Texture ( void )
            : Image   ( NULL )
            , TID     ( 0    )
{
}

CA::Texture::~Texture(void)
{
  if ( NULL != Image ) delete Image ;
}

int CA::Texture::MipSize(int size)
{
  int z = 2                ;
  while ( size > z) z += z ;
  return z                 ;
}

QSize CA::Texture::MipSize(QSize & size)
{
  int w = MipSize ( size . width  ( ) ) ;
  int h = MipSize ( size . height ( ) ) ;
  return QSize    ( w , h             ) ;
}

bool CA::Texture::bindError(void)
{
  GLenum err = (GLenum) ::glGetError ( ) ;
  return ( err != GL_NO_ERROR )          ;
}

bool CA::Texture::BindTexture(QImage * image,GLuint & id)
{
  GLvoid * d = image -> bits   ( )                                         ;
  int      w = image -> width  ( )                                         ;
  int      h = image -> height ( )                                         ;
  if ( NULL == d     ) return false                                        ;
  ::glPixelStorei   ( GL_UNPACK_ALIGNMENT , 1                            ) ;
  if ( bindError ( ) ) return false                                        ;
  ::glGenTextures   ( 1            , &id                                 ) ;
  if ( bindError ( ) ) return false                                        ;
  ::glBindTexture   ( GL_TEXTURE_2D , id                                 ) ;
  if ( bindError ( ) ) return false                                        ;
  ::glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S     , GL_CLAMP   ) ;
  if ( bindError ( ) ) return false                                        ;
  ::glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T     , GL_CLAMP   ) ;
  if ( bindError ( ) ) return false                                        ;
  ::glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_NEAREST ) ;
  if ( bindError ( ) ) return false                                        ;
  ::glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST ) ;
  if ( bindError ( ) ) return false                                        ;
//  ::glTexEnvf       ( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_REPLACE  ) ;
  ::glTexEnvi       ( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE ) ;
  if ( bindError ( ) ) return false                                        ;
  ::glTexImage2D    ( GL_TEXTURE_2D                                        ,
                      0                                                    ,
                      GL_RGBA                                              ,
                      w                                                    ,
                      h                                                    ,
                      0                                                    ,
                      GL_RGBA                                              ,
                      GL_UNSIGNED_BYTE                                     ,
                      d                                                  ) ;
  if ( bindError ( ) ) return false                                        ;
  return true                                                              ;
}

bool CA::Texture::loadResource(QString res)
{
  QImage * I                                                                 ;
  QImage * X                                                                 ;
  QSize    O                                                                 ;
  QSize    S                                                                 ;
    I  = new QImage (     )                                                  ;
  (*I) =     QImage ( res )                                                  ;
  if ( NULL == I ) return false                                              ;
  ////////////////////////////////////////////////////////////////////////////
  O = I -> size (   )                                                        ;
  S = MipSize   ( O )                                                        ;
  ////////////////////////////////////////////////////////////////////////////
  X = new QImage ( )                                                         ;
  (*X) = I -> scaled ( S , Qt::KeepAspectRatio , Qt::SmoothTransformation  ) ;
  delete I                                                                   ;
  ////////////////////////////////////////////////////////////////////////////
  if ( NULL != Image ) delete Image                                          ;
    Image  = new QImage ( )                                                  ;
  (*Image) = X -> convertToFormat ( QImage::Format_RGBA8888 )                ;
  delete X                                                                   ;
  ////////////////////////////////////////////////////////////////////////////
  Original = O                                                               ;
  Size     = S                                                               ;
  ////////////////////////////////////////////////////////////////////////////
  return true                                                                ;
}

bool CA::Texture::Bind(void)
{
  return BindTexture ( Image , TID ) ;
}

bool CA::Texture::Release(void)
{
  ::glDeleteTextures ( 1 , & TID               )              ;
  if                 ( bindError ( )           ) return false ;
  ::glPixelStorei    ( GL_UNPACK_ALIGNMENT , 4 )              ;
  if                 ( bindError ( )           ) return false ;
  return true                                                 ;
}

void CA::Texture::Render(void)
{
  double w = Original . width  ( )   ;
  double h = Original . height ( )   ;
  ////////////////////////////////////
  ::glBegin      ( GL_QUADS        ) ;
  ////////////////////////////////////
  ::glTexCoord2d ( 0.0 , 1.0       ) ;
  ::glVertex3d   ( 0.0 , 0.0 , 0.0 ) ;
  ::glTexCoord2d ( 1.0 , 1.0       ) ;
  ::glVertex3d   ( w   , 0.0 , 0.0 ) ;
  ::glTexCoord2d ( 1.0 , 0.0       ) ;
  ::glVertex3d   ( w   , h   , 0.0 ) ;
  ::glTexCoord2d ( 0.0 , 0.0       ) ;
  ::glVertex3d   ( 0   , h   , 0.0 ) ;
  ////////////////////////////////////
  ::glEnd        (                 ) ;
}
