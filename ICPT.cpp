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
  Parse            ( argc , argv ) ;
  ui    -> setupUi ( this        ) ;
  mdi    = ui -> Center            ;
  curves = NULL                    ;
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
  show                                       (           ) ;
  //////////////////////////////////////////////////////////
  QObject::connect ( this , SIGNAL ( EmitStart ( ) )       ,
                     this , SLOT   ( Start     ( ) )     ) ;
  emit EmitStart ( )                                       ;
  //////////////////////////////////////////////////////////
  return true                                              ;
}

void ICPT::Start(void)
{
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

void ICPT::StopScenes(void)
{
  if ( NULL == curves ) return ;
  curves -> StopTime ( )       ;
}
