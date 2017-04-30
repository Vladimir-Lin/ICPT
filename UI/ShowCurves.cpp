#include "ShowCurves.hpp"

ShowCurves:: ShowCurves       ( QWidget * parent )
           : QOpenGLWidget    (           parent )
           , QOpenGLFunctions (                  )
{
  double * v = V4 . values ( )                         ;
  QObject::connect ( &TTT , SIGNAL ( timeout   ( ) )   ,
                     this , SLOT   ( Intervals ( ) ) ) ;
  v [ 0 ] = 15000.0                                    ;
  v [ 1 ] = -5000.0                                    ;
  v [ 2 ] =  5000.0                                    ;
  v [ 3 ] =     0.0                                    ;
}

ShowCurves::~ShowCurves(void)
{
  TTT.stop();
  makeCurrent ( ) ;
  doneCurrent ( ) ;
}

QSize ShowCurves::sizeHint(void) const
{
  return QSize ( 640 , 480 ) ;
}

void ShowCurves::StartTime(void)
{
  TTT . start ( 50 ) ;
}

void ShowCurves::StopTime(void)
{
  TTT . stop ( ) ;
}

void ShowCurves::FlushGL(void)
{
  update ( ) ;
}

void ShowCurves::Intervals(void)
{
  double * v = V4 . values ( )            ;
  v [ 3 ] += 0.5                          ;
  if ( v [ 3 ] > 360.0 ) v [ 3 ] -= 360.0 ;
  double a = v [ 3 ]                      ;
  a       *= M_PI                         ;
  a       /= 180                          ;
  v [ 0 ]  = 15000 * cos ( a )            ;
  v [ 1 ]  = 15000 * sin ( a )            ;
  update ( )                              ;
}

void ShowCurves::initializeGL(void)
{
  initializeOpenGLFunctions ( ) ;
}

void ShowCurves::paintGL(void)
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
  ::glViewport        ( 0 , 0 , w , h                                 ) ;
  ::glMatrixMode      ( GL_TEXTURE                                    ) ;
  ::glLoadIdentity    (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  ::glMatrixMode      ( GL_PROJECTION                                 ) ;
  ::glLoadIdentity    (                                               ) ;
  ::gluPerspective    ( 45 , factor , 1 , 10000000000000000000.0      ) ;
  ::glMatrixMode      ( GL_MODELVIEW                                  ) ;
  ::glLoadIdentity    (                                               ) ;
  ::gluLookAt         ( v [ 0 ] , v [ 1 ] ,  v [ 2 ]                    ,
                            0.0 ,     0.0 ,      0.0                    ,
                            0.0 ,     0.0 ,      1.0                  ) ;
  ::glPushMatrix      (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  DrawCurves          (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  ::glPopMatrix       (                                               ) ;
  ::glFlush           (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
}

void ShowCurves::resizeGL(int width,int height)
{
}

bool ShowCurves::bindError(void)
{
  GLenum err = (GLenum) ::glGetError ( ) ;
  return ( err != GL_NO_ERROR )          ;
}

bool ShowCurves::BindTexture(QImage * image,GLuint & id)
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

void ShowCurves::PushPoints(int n,int gaps,double * points)
{
  for ( int i = 0 , p = 0 ; i < n ; i++ , p += gaps ) {
    ::glVertex3dv ( & points [ p ] )                  ;
  }                                                   ;
}

void ShowCurves::DrawCurves(void)
{
  ::glLineWidth ( 2.5                       ) ;
  /////////////////////////////////////////////
  ::glColor4f   ( 1.0f , 0.0f , 0.0f , 1.0f ) ;
  ::glBegin     ( GL_LINES                  ) ;
  ::glVertex3f  ( -10000 , 0 , 0            ) ;
  ::glVertex3f  (  10000 , 0 , 0            ) ;
  ::glEnd       (                           ) ;
  /////////////////////////////////////////////
  ::glColor4f   ( 0.0f , 1.0f , 0.0f , 1.0f ) ;
  ::glBegin     ( GL_LINES                  ) ;
  ::glVertex3f  ( 0 ,      0 , 0            ) ;
  ::glVertex3f  ( 0 ,  10000 , 0            ) ;
  ::glEnd       (                           ) ;
  /////////////////////////////////////////////
  ::glColor4f   ( 0.0f , 0.0f , 1.0f , 1.0f ) ;
  ::glBegin     ( GL_LINES                  ) ;
  ::glVertex3f  ( 0 , 0 , -10000            ) ;
  ::glVertex3f  ( 0 , 0 ,  10000            ) ;
  ::glEnd       (                           ) ;
  /////////////////////////////////////////////
  CA::Catastrophe::Fold fold                  ;
  double                a = 1.0               ;
  double                b = 0.0               ;
  double                c = 0.0               ;
  double                x                     ;
  double                y                     ;
  double                z                     ;
  double                vp                    ;
  double                vpp                   ;
  /////////////////////////////////////////////
  ::glColor4f   ( 0.2f , 0.4f , 0.5f , 1.0f ) ;
  /////////////////////////////////////////////
  for ( int B = -300 ; B <= 300 ; B++ )       {
  ::glBegin     ( GL_LINE_STRIP             ) ;
  for ( int X = -75 ; X <= 75 ; X++ )         {
    b    = B                                  ;
    x    = X                                  ;
    b   *= 100                                ;
    x   *= 2                                  ;
    fold . setParameters ( a , b , c )        ;
    y    = fold . Z      (           )        ;
    fold . CalculateX    ( x         )        ;
    z    = fold . V      (           )        ;
    vp   = fold . Vp     (           )        ;
    x   *=   50                               ;
    y   /=    5                               ;
    z   /=   2000                             ;
    vp  /= 100000                             ;
    vpp  = X                                  ;
    vpp +=     75                             ;
    vpp /=    150                             ;
    vpp /=      2                             ;
    if ( vp < 0 )                             {
      vp = -vp                                ;
      if ( vp > 1.0 ) vp = 1.0                ;
      ::glColor4f ( 0.5f  , vpp , vp , 1.0f ) ;
    } else
    if ( vp > 0 )                             {
      if ( vp > 1.0 ) vp = 1.0                ;
      ::glColor4f ( vp , vpp  , 0.5f , 1.0f ) ;
    } else                                    {
      ::glColor4f ( 0.2f,0.4f , 0.5f , 1.0f ) ;
    }                                         ;
    ::glVertex3d         ( x , y , z )        ;
  }                                           ;
  ::glEnd       (                           ) ;
  }                                           ;
  /////////////////////////////////////////////
}
