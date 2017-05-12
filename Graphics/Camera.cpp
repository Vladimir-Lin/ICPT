#include "Graphics.hpp"

CA::Camera:: Camera (void)
{
  Mode  = PERSPECTIVE ;
  Stare = NOTHING     ;
  Eye   . zero ( )    ;
  At    . zero ( )    ;
  Up    . zero ( )    ;
}

CA::Camera::~Camera (void)
{
}

CA::Vector4 & CA::Camera::value(int index)
{
  switch ( index )        {
    case EYE : return Eye ;
    case AT  : return At  ;
    case UP  : return Up  ;
  }                       ;
  return Vector4 ( )      ;
}

void CA::Camera::setRegion(QRectF & region)
{
  double * T = To . values ( )                          ;
  Region     = region                                   ;
  T [ 2 ]    = region . width ( ) / region . height ( ) ;
}

void CA::Camera::setRegion          (
       double left  , double top    ,
       double width , double height )
{
  double * T = To . values ( )  ;
  Region . setLeft   ( left   ) ;
  Region . setTop    ( top    ) ;
  Region . setWidth  ( width  ) ;
  Region . setHeight ( height ) ;
  T [ 2 ] = width / height      ;
}

void CA::Camera::Orthogonal                   (
       double Left ,double Bottom,double Near ,
       double Right,double Top   ,double Far  )
{
  From . setValues ( Left  , Bottom , Near , 0.0 ) ;
  To   . setValues ( Right , Top    , Far  , 0.0 ) ;
  Mode = ORTHOGONAL                                ;
}

void CA::Camera::Frustum                          (
       double Left  , double Bottom , double Near ,
       double Right , double Top    , double Far  )
{
  From . setValues ( Left  , Bottom , Near , 0.0 ) ;
  To   . setValues ( Right , Top    , Far  , 0.0 ) ;
  Mode = FRUSTUM                                   ;
}

void CA::Camera::Projection(double FOV,double W,double H,double N,double F)
{
  double f = W / H                       ;
  From . setValues ( W , H , FOV , 0.0 ) ;
  To   . setValues ( N , F , f   , 0.0 ) ;
  Mode = PERSPECTIVE                     ;
}

void CA::Camera::Projection(double FOV,double W,double H)
{
  Projection ( FOV , W , H , 1.0 , 1000000000000000000000000000000000000000000.0 ) ;
}

void CA::Camera::Projection(double FOV)
{
  Projection ( FOV , Region . width ( ) , Region . height ( ) ) ;
}

void CA::Camera::Look(Vector4 & eye,Vector4 & at,Vector4 & up)
{
  Eye   = eye    ;
  At    = at     ;
  Up    = up     ;
  Stare = LOOKAT ;
}

void CA::Camera::LookAt(void)
{
  double * E = Eye . values ( )                ;
  double * A = At  . values ( )                ;
  double * U = Up  . values ( )                ;
  ::gluLookAt ( E [ 0 ] , E [ 1 ] ,  E [ 2 ]   ,
                A [ 0 ] , A [ 1 ] ,  A [ 2 ]   ,
                U [ 0 ] , U [ 1 ] ,  U [ 2 ] ) ;
}

void CA::Camera::Viewport(void)
{
  double L = Region . left   ( ) ;
  double T = Region . top    ( ) ;
  double W = Region . width  ( ) ;
  double H = Region . height ( ) ;
  ::glViewport ( L , T , W , H ) ;
}

void CA::Camera::doOrthogonal(void)
{
  double * F = From . values ( )  ;
  double * T = To   . values ( )  ;
  ::glOrtho ( F [ 0 ] , T [ 0 ]   ,
              F [ 1 ] , T [ 1 ]   ,
              F [ 2 ] , T [ 2 ] ) ;
}

void CA::Camera::doFrustum(void)
{
  double * F = From . values ( )    ;
  double * T = To   . values ( )    ;
  ::glFrustum ( F [ 0 ] , T [ 0 ]   ,
                F [ 1 ] , T [ 1 ]   ,
                F [ 2 ] , T [ 2 ] ) ;
}

void CA::Camera::doPerspective(void)
{
  double * F = From . values ( )                             ;
  double * T = To   . values ( )                             ;
  ::gluPerspective ( F [ 2 ] , T [ 2 ] , T [ 0 ] , T [ 1 ] ) ;
}

void CA::Camera::Prepare(void)
{
}

void CA::Camera::Push(void)
{
  double * P = Project . values ( )              ;
  double * M = Model   . values ( )              ;
  Prepare           (                          ) ;
  Viewport          (                          ) ;
  ::glMatrixMode    ( GL_PROJECTION            ) ;
  ::glLoadIdentity  (                          ) ;
  switch ( Mode )                                {
    case ORTHOGONAL                              :
      doOrthogonal  (                          ) ;
    break                                        ;
    case FRUSTUM                                 :
      doFrustum     (                          ) ;
    break                                        ;
    case PERSPECTIVE                             :
      doPerspective (                          ) ;
    break                                        ;
  }                                              ;
  glGetDoublev      ( GL_PROJECTION_MATRIX , P ) ;
  ::glMatrixMode    ( GL_MODELVIEW             ) ;
  ::glLoadIdentity  (                          ) ;
  switch ( Stare )                               {
    case NOTHING                                 :
    break                                        ;
    case LOOKAT                                  :
      LookAt        (                          ) ;
    break                                        ;
  }                                              ;
  ::glGetDoublev    ( GL_MODELVIEW_MATRIX  , M ) ;
  ::glPushMatrix    (                          ) ;
  ////////////////////////////////////////////////
  GetIn = Model . transpose (        )           ;
  GetIn . inverse           ( GetOut )           ;
}

void CA::Camera::Pop(void)
{
  ::glPopMatrix    (               ) ;
}
