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
  Parse         ( argc , argv ) ;
  ui -> setupUi ( this        ) ;
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
