#include "ShowCurves.hpp"

StarView:: StarView         ( QWidget * parent )
         : QOpenGLWidget    (           parent )
         , QOpenGLFunctions (                  )
{
  CA::Vector4 AT ( 0.0 , 0.0 , 0.0 , 0.0 )                ;
  CA::Vector4 UP ( 0.0 , 0.0 , 1.0 , 0.0 )                ;
  QObject::connect ( &TTT , SIGNAL ( timeout   ( ) )      ,
                     this , SLOT   ( Intervals ( ) )    ) ;
  V4     . setValues ( 15000.0 , -5000.0 , 5000.0 , 0.0 ) ;
  camera . Look      ( V4      , AT , UP                ) ;
}

StarView::~StarView(void)
{
  TTT . stop  ( ) ;
  makeCurrent ( ) ;
  doneCurrent ( ) ;
}

QSize StarView::sizeHint(void) const
{
  return QSize ( 640 , 480 ) ;
}

void StarView::StartTime(void)
{
  TTT . start ( 50 ) ;
}

void StarView::StopTime(void)
{
  TTT . stop ( ) ;
}

void StarView::FlushGL(void)
{
  update ( ) ;
}

void StarView::Intervals(void)
{
  update ( ) ;
}

void StarView::mousePressEvent(QMouseEvent * e)
{
  QWidget::mousePressEvent ( e ) ;
}

void StarView::mouseReleaseEvent(QMouseEvent * e)
{
  QWidget::mouseReleaseEvent ( e ) ;
}

void StarView::mouseDoubleClickEvent(QMouseEvent * e)
{
  QWidget::mouseDoubleClickEvent ( e ) ;
}

void StarView::mouseMoveEvent(QMouseEvent * e)
{
  QWidget::mouseMoveEvent ( e ) ;
}

void StarView::initializeGL(void)
{
  initializeOpenGLFunctions (                             ) ;
  camera . Projection       ( 45 , width ( ) , height ( ) ) ;
}

void StarView::paintGL(void)
{
  ::glEnable          ( GL_DEPTH_TEST                                 ) ;
//  ::glDisable         ( GL_DEPTH_TEST                                 ) ;
//  ::glDepthFunc       ( GL_NEVER                                      ) ;
  ::glDepthFunc       ( GL_LESS                                       ) ;
//  ::glDepthFunc       ( GL_EQUAL                                      ) ;
//  ::glDepthFunc       ( GL_LEQUAL                                     ) ;
//  ::glDepthFunc       ( GL_GREATER                                    ) ;
//  ::glDepthFunc       ( GL_NOTEQUAL                                   ) ;
//  ::glDepthFunc       ( GL_GEQUAL                                     ) ;
//  ::glDepthFunc       ( GL_ALWAYS                                     ) ;
//  ::glEnable          ( GL_CULL_FACE                                  ) ;
  ::glDisable         ( GL_CULL_FACE                                  ) ;
  ::glCullFace        ( GL_BACK                                       ) ;
//  ::glCullFace        ( GL_FRONT                                      ) ;
//  ::glCullFace        ( GL_FRONT_AND_BACK                             ) ;
  ::glEnable          ( GL_BLEND                                      ) ;
  ::glBlendFunc       ( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA         ) ;
  ::glEnable          ( GL_COLOR_MATERIAL                             ) ;
//  ::glColorMaterial   ( GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE    ) ;
  ::glShadeModel      ( GL_SMOOTH                                     ) ;
  ::glEnable          ( GL_LINE_SMOOTH                                ) ;
  ::glHint            ( GL_LINE_SMOOTH_HINT , GL_NICEST               ) ;
  ::glClearColor      ( 1.0 , 1.0 , 1.0 , 1.0                         ) ;
//  ::glClearColor      ( 0.0f , 0.204f , 0.400f , 1.0f                 ) ;
  ::glClear           ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT     ) ;
  ///////////////////////////////////////////////////////////////////////
  int      w      = width  ( )                                          ;
  int      h      = height ( )                                          ;
  double   factor = w                                                   ;
  double * v      = V4 . values ( )                                     ;
  factor /= h                                                           ;
  ///////////////////////////////////////////////////////////////////////
  ::glMatrixMode      ( GL_TEXTURE                                    ) ;
  ::glLoadIdentity    (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  camera . Push       (                                               ) ;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  camera . Pop        (                                               ) ;
  ::glFlush           (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
}

void StarView::resizeGL(int width,int height)
{
  camera . setRegion ( 0 , 0 , width , height ) ;
}

bool StarView::bindError(void)
{
  GLenum err = (GLenum) ::glGetError ( ) ;
  return ( err != GL_NO_ERROR )          ;
}

bool StarView::BindTexture(QImage * image,GLuint & id)
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

void StarView::PushPoints(int n,int gaps,double * points)
{
  for ( int i = 0 , p = 0 ; i < n ; i++ , p += gaps ) {
    ::glVertex3dv ( & points [ p ] )                  ;
  }                                                   ;
}
