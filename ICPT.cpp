#include "ICPT.hpp"
#include "ui_ICPT.h"

//////////////////////////////////////////////////////////////////////////////

int main(int argc,char * argv[])
{
  QApplication a           ( argc , argv     ) ;
  ICPT         w           ( argc , argv     ) ;
  if                       ( w . Prepare ( ) ) {
    return     a . exec    (                 ) ;
  }                                            ;
  return       w . Failure (                 ) ;
}

//////////////////////////////////////////////////////////////////////////////

ICPT:: ICPT          ( int argc , char ** argv , QWidget * parent )
     : QMainWindow   (                                     parent )
     , CA::Destroyer (                                            )
     , CA::Thread    (                                            )
     , ui            ( new Ui::ICPT                               )
{
  Parse             ( argc , argv ) ;
  ui     -> setupUi ( this        ) ;
  mdi     = ui -> Center            ;
  gallery = NULL                    ;
  curves  = NULL                    ;
}

ICPT::~ICPT(void)
{
  delete ui ;
}

void ICPT::Parse(int argc,char ** argv)
{
  if ( argc <= 1 ) return ;
}

int ICPT::Failure(void)
{
  return 0 ;
}

void ICPT::Quit(void)
{
  qApp-> quit ( ) ;
//  qApp -> quitOnLastWindowClosed ( ) ;
}

bool ICPT::Prepare(void)
{
  ///////////////////////////////////////////////////////////////////////
  QObject::connect ( this , SIGNAL ( EmitStart ( ) )                    ,
                     this , SLOT   ( Start     ( ) )                  ) ;
  ///////////////////////////////////////////////////////////////////////
  QObject::connect ( ui -> menuMonitors , SIGNAL ( aboutToShow  ( ) )   ,
                     this               , SLOT   ( ShowMonitors ( ) ) ) ;
  ///////////////////////////////////////////////////////////////////////
  QObject::connect ( ui -> menuWindows  , SIGNAL ( aboutToShow  ( ) )   ,
                     this               , SLOT   ( ShowWindows  ( ) ) ) ;
  ///////////////////////////////////////////////////////////////////////
  emit EmitStart ( )                                                    ;
  ///////////////////////////////////////////////////////////////////////
  return true                                                           ;
}

void ICPT::Start(void)
{
  show              ( ) ;
  CreateInterpreter ( ) ;
}

void ICPT::CreateInterpreter(void)
{
  QScrollArea * sa = NULL                                    ;
  ////////////////////////////////////////////////////////////
  dock  = new QDockWidget       (                          ) ;
  dock -> setAllowedAreas       ( Qt::TopDockWidgetArea      |
                                  Qt::BottomDockWidgetArea ) ;
  dock -> setWindowTitle        ( tr("Commands")           ) ;
  addDockWidget                 ( Qt::BottomDockWidgetArea   ,
                                  dock                       ,
                                  Qt::Vertical             ) ;
  ////////////////////////////////////////////////////////////
  sa    = new QScrollArea       (                          ) ;
  sa   -> setMinimumHeight      ( 120                      ) ;
  dock -> setWidget             ( sa                       ) ;
  cli   = new InteractiveEditor ( sa                       ) ;
}

void ICPT::ShowMonitors(void)
{
  QMenu   * mm = ui   -> menuMonitors                            ;
  int       sc = qApp -> desktop ( ) -> screenCount ( )          ;
  QString   ss                                                   ;
  QAction * aa                                                   ;
  QRect     rr                                                   ;
  ////////////////////////////////////////////////////////////////
  mm -> clear ( )                                                ;
  ////////////////////////////////////////////////////////////////
  for ( int i = 0 ; i < sc ; i++ )                               {
    rr  = qApp -> desktop ( ) -> screenGeometry ( i )            ;
    ss  = tr ( "Screen %1 : %2 X %3 ( %4 , %5 )"                 )
          . arg ( i                                              )
          . arg ( rr . width  ( )                                )
          . arg ( rr . height ( )                                )
          . arg ( rr . left   ( )                                )
          . arg ( rr . top    ( )                              ) ;
    aa  = new QAction (    )                                     ;
    aa -> setText     ( ss )                                     ;
    mm -> addAction   ( aa )                                     ;
  }                                                              ;
}

void ICPT::ShowWindows(void)
{
  QMenu               *  mm   = ui  -> menuWindows       ;
  QList<QMdiSubWindow *> LMSW = mdi -> subWindowList ( ) ;
  int                    sc   = LMSW . count         ( ) ;
  QString                ss                              ;
  QAction             *  aa                              ;
  ////////////////////////////////////////////////////////
  mm -> clear ( )                                        ;
  ////////////////////////////////////////////////////////
  for ( int i = 0 ; i < sc ; i++ )                       {
    ss  = LMSW [ i ] -> windowTitle ( )                  ;
    aa  = new QAction (                                ) ;
    aa -> setText     ( ss                             ) ;
    aa -> setIcon     ( LMSW [ i ] -> windowIcon ( )   ) ;
    mm -> addAction   ( aa                             ) ;
  }                                                      ;
}

void ICPT::Play(void)
{
}

void ICPT::Scenes(void)
{
  curves  = new ShowCurves ( NULL     ) ;
  mdi    -> addSubWindow   ( curves   ) ;
  curves -> show           (          ) ;
  curves -> setWindowTitle ( "Curves" ) ;
  curves -> StartTime      (          ) ;
}


void PrintV(CA::Vector4 & v)
{
  double * V = v . values ( ) ;
  printf ( "%g\n%g\n%g\n%g\n" , V[0] , V[1] , V[2] , V[3] ) ;
}

void ICPT::StopScenes(void)
{
  if ( NULL == curves ) return ;
  curves -> StopTime ( )       ;
}

void ICPT::Gallery(bool enabled)
{
  if                                     ( enabled         ) {
    if                                   ( NULL == gallery ) {
      gallery = new GalleryView          ( NULL            ) ;
      mdi    -> addSubWindow             ( gallery         ) ;
    }                                                        ;
    gallery  -> parentWidget ( ) -> show (                 ) ;
  } else                                                     {
    gallery  -> parentWidget ( ) -> hide (                 ) ;
  }                                                          ;
}

void ICPT::NewWorld(void)
{
  StarView * sv                         ;
  sv   = new StarView   ( NULL        ) ;
  mdi -> addSubWindow   ( sv          ) ;
  sv  -> show           (             ) ;
  sv  -> setWindowTitle ( "Star View" ) ;
  sv  -> StartTime      (             ) ;
  sv  -> start          ( 10003       ) ;
}

void ICPT::FullWorld(void)
{
  StarView * sv                         ;
  sv   = new StarView   ( NULL        ) ;
  sv  -> setWindowTitle ( "Star View" ) ;
  sv  -> showFullScreen (             ) ;
  sv  -> StartTime      (             ) ;
  sv  -> start          ( 10003       ) ;
}
