#include "ShowCurves.hpp"

StarView:: StarView         ( QWidget * parent )
         : QOpenGLWidget    (           parent )
         , CA::Thread       (                  )
         , QOpenGLFunctions (                  )
{
  CA::Light * l = new CA::Light ( )                                          ;
  double      FFF =     15.0                                                 ;
  double      Efp = 152100.0000                                              ;
  double      Elp = 147095.0000                                              ;
  double      Eap = 149598.0230                                              ;
  double      Eee =      0.0167086                                           ;
  double      Mfp =    405.6960                                              ;
  double      Mlp =    363.1040                                              ;
  double      Map =    384.3990                                              ;
  double      Mee =      5.1450                                              ;
  double      Oee =      0.0549                                              ;
  double      Rp  =      6.3568                                              ;
  double      Re  =      6.3781                                              ;
  double      Mp  =      1.7381                                              ;
  double      Me  =      1.7360                                              ;
  double      Sp  =    695.5000                                              ;
  double      Se  =    695.5000                                              ;
  double      L2  =   1496.4040                                              ;
  int         n   =    720                                                   ;
  int         m   =    180                                                   ;
  double      Xp  = Efp + ( L2 / 4 )                                         ;
  double      Yp  = L2  / 2                                                  ;
  double      Exp = Efp - Eap                                                ;
  double      Ebp                                                            ;
  double      Mav = M_PI * Mee / 180.0                                       ;
  double      Mcv = cos ( Mav )                                              ;
  double      Msv = sin ( Mav )                                              ;
  ////////////////////////////////////////////////////////////////////////////
  CA::Vector4 AT ( Efp - ( L2 / 8 ) , 0.0 , 0.0 , 0.0 )                      ;
  CA::Vector4 UP ( 0.0 , 0.0 , 1.0 , 0.0 )                                   ;
  ////////////////////////////////////////////////////////////////////////////
  QObject::connect       ( &TTT , SIGNAL ( timeout   ( ) )                   ,
                           this , SLOT   ( Intervals ( ) )                 ) ;
  V4     . setValues     ( Xp , Yp , 100.0 , 0.0                           ) ;
  camera . Look          ( V4 , AT , UP                                    ) ;
  ////////////////////////////////////////////////////////////////////////////
  Earth  . loadTexture   ( ":/images/earth.jpg"                            ) ;
  Earth  . setRadius     ( Re , Re , Rp                                    ) ;
  Earth  . setSegments   ( n  , m                                          ) ;
  Earth  . Generate      (                                                 ) ;
  Epp    . T . setValues (  Efp ,  0.0 ,  0.0 , 0.0                        ) ;
  Epp    . A . setValues (  0.0 ,  1.0 ,  0.0 , 360.0 - 23.4392811         ) ;
  Epp    . R . setValues (  0.0 ,  0.0 ,  1.0 , 0.0                        ) ;
  Epp    . S . setValues (  FFF ,  FFF ,  FFF , 1.0                        ) ;
  ////////////////////////////////////////////////////////////////////////////
  Moon   . loadTexture   ( ":/images/moon.jpg"                             ) ;
  Moon   . setRadius     ( Me , Me , Mp                                    ) ;
  Moon   . setSegments   ( n  , m                                          ) ;
  Moon   . Generate      (                                                 ) ;
  Mpp    . T . setValues ( Efp + ( Mfp * Mcv) , 0.0 , -Msv * Mfp , 0.0     ) ;
  Mpp    . A . setValues (       0.0 ,  1.0 ,  0.0 , 1.5424                ) ;
  Mpp    . R . setValues (       0.0 ,  0.0 ,  1.0 , 0.0                   ) ;
  Mpp    . S . setValues (       FFF ,  FFF ,  FFF , 1.0                   ) ;
  ////////////////////////////////////////////////////////////////////////////
//  Sun    . loadTexture  ( ":/images/sun.jpg"                              ) ;
  Sun    . setRadius     ( Se , Se , Sp                                    ) ;
  Sun    . setSegments   ( n  , m                                          ) ;
  Sun    . Generate      (                                                 ) ;
  Spp    . T . setValues (   0.0 ,   0.0 ,   0.0 , 0.00                    ) ;
  Spp    . A . setValues (   0.0 ,   1.0 ,   0.0 , 7.25                    ) ;
  Spp    . R . setValues (   0.0 ,   0.0 ,   1.0 , 0.00                    ) ;
  Spp    . S . setValues (  12.0 ,  12.0 ,  12.0 , 1.00                    ) ;
  ////////////////////////////////////////////////////////////////////////////
  Ebp     = Eap * sqrt ( 1 - ( Eee * Eee ) )                                 ;
  esOrbit = new double [ 36000 * 4 ]                                         ;
  for ( int i = 0 ; i < 36000 ; i++ )                                        {
    double a                                                                 ;
    double x                                                                 ;
    double y                                                                 ;
    int    i4 = i * 4                                                        ;
    a                  = M_PI * i / 18000                                    ;
    x                  = Eap * cos ( a )                                     ;
    y                  = Ebp * sin ( a )                                     ;
    esOrbit [ i4     ] = x                                                   ;
    esOrbit [ i4 + 1 ] = y                                                   ;
    esOrbit [ i4 + 2 ] = 0.0                                                 ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  emOrbit = new double [ 36000 * 4 ]                                         ;
  Ebp     = Map * sqrt ( 1 - ( Oee * Oee ) )                                 ;
  Mav     = M_PI * Mee / 180.0                                               ;
  Mcv     = cos ( Mav )                                                      ;
  Msv     = sin ( Mav )                                                      ;
  Exp     = Mfp - Map                                                        ;
  for ( int i = 0 ; i < 36000 ; i++ )                                        {
    double a                                                                 ;
    double b                                                                 ;
    double x                                                                 ;
    double y                                                                 ;
    double z                                                                 ;
    int    i4 = i * 4                                                        ;
    a                  = M_PI * i / 18000                                    ;
    x                  = ( Map * cos ( a ) )                                 ;
    y                  =   Ebp * sin ( a )                                   ;
    z                  = x * Msv                                             ;
    x                 *= Mcv                                                 ;
    y                 *= Mcv                                                 ;
    x                 += Exp                                                 ;
    x                 += Efp                                                 ;
    emOrbit [ i4     ] =  x                                                  ;
    emOrbit [ i4 + 1 ] =  y                                                  ;
    emOrbit [ i4 + 2 ] = -z                                                  ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  material . setId      ( 137                              )                 ;
  material . setName    ( tr("Material")                   )                 ;
  ////////////////////////////////////////////////////////////////////////////
  material . setEnabled ( CA::Material::AMBIENT   , true   )                 ;
  material . setEnabled ( CA::Material::DIFFUSE   , true   )                 ;
  material . setEnabled ( CA::Material::SPECULAR  , true   )                 ;
  material . setEnabled ( CA::Material::SHININESS , true   )                 ;
  material . setEnabled ( CA::Material::EMISSION  , true   )                 ;
  ////////////////////////////////////////////////////////////////////////////
  material . setData    ( CA::Material::AMBIENT                              ,
                           0.6 , 0.6 , 0.6 , 1.0                           ) ;
  material . setData    ( CA::Material::DIFFUSE                              ,
                           0.9 , 0.9 , 0.9 , 1.0                           ) ;
  material . setData    ( CA::Material::SPECULAR                             ,
                           0.7 , 0.7 , 0.7 , 1.0                           ) ;
  material . setData    ( CA::Material::SHININESS                            ,
                          90.0 , 0.0 , 0.0 , 0.0                           ) ;
  ////////////////////////////////////////////////////////////////////////////
  l -> setId        ( 111                                                  ) ;
  l -> setName      ( tr("Top light")                                      ) ;
  l -> setEnabled   ( CA::Light::COLORS      , true                        ) ;
//  l -> setEnabled   ( CA::Light::SPOT        , false                       ) ;
//  l -> setEnabled   ( CA::Light::ATTENUATION , false                       ) ;
  ////////////////////////////////////////////////////////////////////////////
  l -> setData      ( CA::Light::POSITION                                    ,
                      0.0 ,      0.0 ,     0.0 , 1.0                       ) ;
  ////////////////////////////////////////////////////////////////////////////
  l -> setData      ( CA::Light::AMBIENT                                     ,
                       0.60 , 0.60 , 0.60 , 1.00                           ) ;
  l -> setData      ( CA::Light::DIFFUSE                                     ,
                       0.90 , 0.90 , 0.90 , 1.00                           ) ;
  l -> setData      ( CA::Light::SPECULAR                                    ,
                       0.80 , 0.80 , 0.80 , 1.00                           ) ;
  ////////////////////////////////////////////////////////////////////////////
  lights . addLight ( l                                                    ) ;
  ////////////////////////////////////////////////////////////////////////////
  rendering   = false                                                        ;
  interval    = 75                                                           ;
  cameraAngle = 0                                                            ;
  zAngle      = 0                                                            ;
}

StarView::~StarView(void)
{
  delete [ ] esOrbit ;
  ggg = false        ;
  TTT . stop  ( )    ;
  makeCurrent ( )    ;
  doneCurrent ( )    ;
}

QSize StarView::sizeHint(void) const
{
  return QSize ( 640 , 480 ) ;
}

void StarView::StartTime(void)
{
  TTT . start ( interval ) ;
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
  if ( rendering ) return ;
  update ( )              ;
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
  rendering = true                                                      ;
  ///////////////////////////////////////////////////////////////////////
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
//  ::glClearColor      ( 1.0 , 1.0 , 1.0 , 1.0                         ) ;
  ::glClearColor      ( 0.0 , 0.0 , 0.0 , 0.0                         ) ;
//  ::glClearColor      ( 0.0f , 0.204f , 0.400f , 1.0f                 ) ;
  ::glClear           ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT     ) ;
  ///////////////////////////////////////////////////////////////////////
  ::glMatrixMode      ( GL_TEXTURE                                    ) ;
  ::glLoadIdentity    (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  camera . setRegion  ( 0 , 0 , width ( ) , height ( )                ) ;
  camera . Projection ( 45                                            ) ;
  camera . Push       (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  material . Execute  (                                               ) ;
  lights   . Execute  (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  ::glPushMatrix      (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  Spp . Push          (                                               ) ;
  ::glColor4d         ( 0.75 , 0.75 , 0.0 , 1.0                       ) ;
  Sun   . Surface     (                                               ) ;
  ::glColor4d         ( 1.0 , 0.0 , 0.0 , 0.5                         ) ;
  ::glBegin           ( GL_LINE_STRIP                                 ) ;
  ::glVertex3d        ( 0.0 , 0.0 , -800                              ) ;
  ::glVertex3d        ( 0.0 , 0.0 ,  800                              ) ;
  ::glEnd             (                                               ) ;
  Spp . Pop           (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  Epp . Push          (                                               ) ;
  ::glColor4d         ( 1.0 , 1.0 , 1.0 , 1.0                         ) ;
  Earth . Render      (                                               ) ;
  ::glColor4d         ( 1.0 , 0.0 , 0.0 , 0.5                         ) ;
  ::glBegin           ( GL_LINE_STRIP                                 ) ;
  ::glVertex3d        ( 0.0 , 0.0 , -8                                ) ;
  ::glVertex3d        ( 0.0 , 0.0 ,  8                                ) ;
  ::glEnd             (                                               ) ;
  Epp . Pop           (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  Mpp . Push          (                                               ) ;
  ::glColor4d         ( 1.0 , 1.0 , 1.0 , 1.0                         ) ;
  Moon  . Render      (                                               ) ;
  ::glColor4d         ( 1.0 , 0.0 , 0.0 , 0.5                         ) ;
  ::glBegin           ( GL_LINE_STRIP                                 ) ;
  ::glVertex3d        ( 0.0 , 0.0 , -3                                ) ;
  ::glVertex3d        ( 0.0 , 0.0 ,  3                                ) ;
  ::glEnd             (                                               ) ;
  Mpp . Pop           (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  CA::Vector4 CC                                                        ;
  CC . setValues      ( 0.20 , 1.00 , 0.20 , 1.00                     ) ;
  DrawTail            ( CC , EarthTail                                ) ;
  CC . setValues      ( 1.0 , 0.0 , 1.0 , 1.0                         ) ;
  DrawTail            ( CC , MoonTail                                 ) ;
  ///////////////////////////////////////////////////////////////////////
  double Efp = 149598.0230                                              ;
  ::glColor4d         ( 0.80 , 0.80 , 1.00 , 0.20                     ) ;
  ::glBegin           ( GL_POLYGON                                    ) ;
  PushPoints          ( 36000 , 4 , esOrbit                           ) ;
  ::glEnd             (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  ::glBegin           ( GL_LINE_STRIP                                 ) ;
  ::glVertex3d        ( 0.0 , 0.0 , 0.0                               ) ;
  ::glVertex3d        ( Efp , 0.0 , 0.0                               ) ;
  ::glEnd             (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  ::glColor4d         ( 0.20 , 0.60 , 1.00 , 0.20                     ) ;
  ::glBegin           ( GL_POLYGON                                    ) ;
  PushPoints          ( 36000 , 4 , emOrbit                           ) ;
  ::glEnd             (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  ::glPopMatrix       (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  camera . Pop        (                                               ) ;
  lights . Disable    (                                               ) ;
  ::glFlush           (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  rendering = false                                                     ;
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

void StarView::PushPoints(int n,int gaps,double * points)
{
  for ( int i = 0 , p = 0 ; i < n ; i++ , p += gaps ) {
    ::glVertex3dv ( & points [ p ] )                  ;
  }                                                   ;
}

void StarView::DrawTail(CA::Vector4 C,QList<CA::Vector4> & P)
{
  if ( P . count ( ) < 3 ) return ;
  int      L  = P . count  ( )    ;
  double * vv = C . values ( )    ;
  double * xx                     ;
  ::glLineWidth ( 2.5 )           ;
  ::glBegin ( GL_LINE_STRIP )     ;
  for ( int i = 0 ; i < L ; i++ ) {
    xx = P [ i ] . values ( )     ;
    vv [ 3 ]  = i + 1             ;
    vv [ 3 ] /= L                 ;
    ::glColor4dv  ( vv )          ;
    ::glVertex3dv ( xx )          ;
  }                               ;
  ::glEnd   (               )     ;
}

void StarView::run(int T,CA::ThreadData * D)
{
  switch ( T )        {
    case 10001        :
      SolarSystem ( ) ;
    break             ;
  }                   ;
}

void StarView::SolarSystem(void)
{
  QDateTime T                                                                ;
  QDateTime E                                                                ;
  double    ET  =     86164.098903691                                        ;
  double    MT  =        27.321661    * 86400.0                              ;
  double    ST  =       365.256363004 * 86400.0                              ;
  double    CT  =        11.700000000 * 86400.0                              ;
  double    ZT  =         5.200000000 * 86400.0                              ;
  double    Efp =    152100.0000                                             ;
  double    Elp =    147095.0000                                             ;
  double    Eap =    149598.0230                                             ;
  double    Eee =         0.0167086                                          ;
  double    Mfp =       405.6960                                             ;
  double    Mlp =       363.1040                                             ;
  double    Map =       384.3990                                             ;
  double    Mee =         5.1450                                             ;
  double    Oee =         0.0549                                             ;
  double    Rp  =         6.3568                                             ;
  double    Re  =         6.3781                                             ;
  double    We  =     59700.0000                                             ;
  double    Mp  =         1.7381                                             ;
  double    Me  =         1.7360                                             ;
  double    Wm  =       734.7700                                             ;
  double    Sp  =       695.5000                                             ;
  double    Se  =       695.5000                                             ;
  double    Ws  = 198910000.0000                                             ;
  double    Wes = - We / Ws                                                  ;
  double    L2  =      1496.4040                                             ;
  double    Xp  = Efp + ( L2 / 4 )                                           ;
  double    Yp  = L2  / 2                                                    ;
  double    Exp = Efp / Eap                                                  ;
  double    Emp = Mfp - Map                                                  ;
  double    Ebp = Eap * ::sqrt ( 1 - ( Eee * Eee ) )                         ;
  double    Mbp = Map * ::sqrt ( 1 - ( Oee * Oee ) )                         ;
  double    Mav = M_PI * Mee / 180.0                                         ;
  double    Mcv = cos ( Mav )                                                ;
  double    Msv = sin ( Mav )                                                ;
  int       dS  = 600                                                        ;
  double    dA  = dS * 360 / ET                                              ;
  double    dM  = dS * 360 / MT                                              ;
  double    dT  = dS * 360 / ST                                              ;
  double    dC  = dS * 360 / CT                                              ;
  double    dZ  = dS * 360 / ZT                                              ;
  double    XX                                                               ;
  double    XA                                                               ;
  double    XB                                                               ;
  double    XC                                                               ;
  double    XS                                                               ;
  double *  vv                                                               ;
  ////////////////////////////////////////////////////////////////////////////
  CA::Vector4   A                                                            ;
  CA::Vector4   B                                                            ;
  CA::Vector4   C                                                            ;
  CA::Vector4   D                                                            ;
  CA::Vector4   F                                                            ;
  CA::Vector4   U ( 0.0 , 0.0 , 1.0 , 0.0 )                                  ;
  CA::Matrix4x4 M                                                            ;
  ////////////////////////////////////////////////////////////////////////////
  E   = QDateTime::currentDateTime ( )                                       ;
  ggg = true                                                                 ;
  while ( ggg )                                                              {
    ::Sleep ( 1 )                                                            ;
    if ( rendering                    ) continue                             ;
    T = QDateTime::currentDateTime ( )                                       ;
    if ( E . msecsTo ( T ) < interval ) continue                             ;
    E = T                                                                    ;
    //////////////////////////////////////////////////////////////////////////
    // Earth Moon Orbit Rotation
    vv        = Epp . T . values ( )                                         ;
    XX        = vv [ 3 ]                                                     ;
    XX       += dT                                                           ;
    vv [ 3 ]  = XX                                                           ;
    XX       *= M_PI                                                         ;
    XX       /= 180                                                          ;
    XC        = cos ( XX ) * Eap                                             ;
    XS        = sin ( XX ) * Ebp                                             ;
    vv [ 0 ]  = XC                                                           ;
    vv [ 1 ]  = XS                                                           ;
    vv [ 2 ]  = 0                                                            ;
    //////////////////////////////////////////////////////////////////////////
    // Sun Position
    A         = Epp . T                                                      ;
    A        *= Wes                                                          ;
    Spp . T   = A                                                            ;
    //////////////////////////////////////////////////////////////////////////
    // Earth Self Rotation
    vv        = Epp . R . values ( )                                         ;
    vv [ 3 ] += dA                                                           ;
    if ( vv [ 3 ] > 360.0 ) vv [ 3 ] -= 360.0                                ;
    //////////////////////////////////////////////////////////////////////////
    // Moon Self and Orbit Rotation
    vv        = Mpp . R . values ( )                                         ;
    vv [ 3 ] += dM                                                           ;
    if ( vv [ 3 ] > 360.0 ) vv [ 3 ] -= 360.0                                ;
    //////////////////////////////////////////////////////////////////////////
    XX        = vv [ 3 ]                                                     ;
    XX       *= M_PI                                                         ;
    XX       /= 180                                                          ;
    XC        = cos ( XX ) * Map                                             ;
    XS        = sin ( XX ) * Mbp                                             ;
    XA        = - XC       * Msv                                             ;
    XC       *=              Mcv                                             ;
    XS       *=              Mcv                                             ;
    A         . setValues  ( XC , XS , XA , 0.0 )                            ;
    XA        = A . length (                    )                            ;
    XC        = XA * We / ( We + Wm )                                        ;
    XS        = XA * Wm / ( We + Wm )                                        ;
    XS        = - XS                                                         ;
    A         . normalize ( )                                                ;
    B         = A                                                            ;
    B        *= XC                                                           ;
    F         = Epp . T                                                      ;
    C         = F                                                            ;
    C        += B                                                            ;
    Mpp . T   = C                                                            ;
    B         = A                                                            ;
    B        *= XS                                                           ;
    C         = F                                                            ;
    C        += B                                                            ;
    Epp . T   = C                                                            ;
    //////////////////////////////////////////////////////////////////////////
    vv  = F . values ( )                                                     ;
    for ( int i = 0 ; i < 36000 ; i++ )                                      {
      double a                                                               ;
      double x                                                               ;
      double y                                                               ;
      double z                                                               ;
      int    i4 = i * 4                                                      ;
      a                  = M_PI * i / 18000                                  ;
      x                  = ( Map * cos ( a ) )                               ;
      y                  =   Mbp * sin ( a )                                 ;
      z                  = x * Msv                                           ;
      x                 *= Mcv                                               ;
      y                 *= Mcv                                               ;
      x                 += Emp                                               ;
      emOrbit [ i4     ] =   x + vv [ 0 ]                                    ;
      emOrbit [ i4 + 1 ] =   y + vv [ 1 ]                                    ;
      emOrbit [ i4 + 2 ] = - z + vv [ 2 ]                                    ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    EarthTail . append ( Epp . T )                                           ;
    MoonTail  . append ( Mpp . T )                                           ;
    if ( EarthTail . count ( ) > 20000 ) EarthTail . takeFirst ( )           ;
    if ( MoonTail  . count ( ) > 20000 ) MoonTail  . takeFirst ( )           ;
    //////////////////////////////////////////////////////////////////////////
    // Camera Moving
    cameraAngle += dC                                                        ;
    if ( cameraAngle > 360.0 ) cameraAngle -= 360.0                          ;
    zAngle      += dZ                                                        ;
    if ( zAngle      > 360.0 ) zAngle      -= 360.0                          ;
    D   . setValues ( 0.0 , 0.0 , 1.0 , cameraAngle )                        ;
    M   . rotate    ( D                             )                        ;
    A   . setValues ( 0.0 , 0.0 , 1.0 , 0.0         )                        ;
    B   = Epp . T                                                            ;
    C   = cross ( A , B )                                                    ;
    C   . normalize  ( )                                                     ;
    XC  = B . length ( )                                                     ;
    XS  = XC + L2 * 1.005                                                    ;
    XC  = XC - L2 * 0.500                                                    ;
    XX  =      L2 * 1.505                                                    ;
    XX /= XS                                                                 ;
    XA  = 1 - XX                                                             ;
    XB  = sqrt ( XA * XX )                                                   ;
    XB *= XS                                                                 ;
    XB /= 15                                                                 ;
    C  *= XB                                                                 ;
    C  += B                                                                  ;
    A   . setValues ( 0.0 , 0.0 , 500.0 * cos ( M_PI * zAngle / 180.0 ) , 0.0 ) ;
    C  += A                                                                  ;
    B   . normalize ( )                                                      ;
    B  *= 1.5 * L2                                                           ;
    C  += B                                                                  ;
    B   . normalize ( )                                                      ;
    B  *= XC                                                                 ;
    A   = Epp . T                                                            ;
    C  -= A                                                                  ;
    B  -= A                                                                  ;
    D   = M * C                                                              ;
    C   = D + A                                                              ;
    D   = M * B                                                              ;
    B   = D + A                                                              ;
    //////////////////////////////////////////////////////////////////////////
    camera . Look ( C  , B , U )                                             ;
  }                                                                          ;
}
