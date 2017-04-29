#ifndef ICPT_HPP
#define ICPT_HPP

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <QtScript>
#include <QtXml>

#include "Linear.hpp"
#include "Physics.hpp"
#include "System.hpp"

namespace Ui {
  class ICPT ;
}

class ICPT : public QMainWindow
           , public CA::Destroyer
           , public CA::Thread
{
  Q_OBJECT
  public:

    explicit     ICPT          (int argc,char ** argv,QWidget * parent = 0) ;
    virtual     ~ICPT          (void) ;

    virtual bool Prepare       (void) ;

  protected:

    Ui::ICPT * ui ;

    void         Parse         (int argc,char ** argv) ;

  private:

  public slots:

    virtual int  Failure       (void) ;
    virtual void Quit          (void) ;
    virtual void Play          (void) ;

  protected slots:

    virtual void Start         (void) ;

  private slots:

  signals:

    void         EmitStart     (void) ;

} ;

#endif // ICPT_HPP