#ifndef ICPT_HPP
#define ICPT_HPP

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <QtScript>
#include <QtXml>

#include "Linear.hpp"
#include "Geometry.hpp"
#include "Catastrophe.hpp"
#include "Physics.hpp"
#include "System.hpp"

#include "ShowCurves.hpp"

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

    Ui::ICPT          * ui      ;
    QMdiArea          * mdi     ;
    QDockWidget       * dock    ;
    InteractiveEditor * cli     ;
    GalleryView       * gallery ;
    ShowCurves        * curves  ;

    void         Parse         (int argc,char ** argv) ;

  private:

    void CreateInterpreter     (void) ;

  public slots:

    virtual int  Failure       (void) ;
    virtual void Quit          (void) ;
    virtual void Play          (void) ;

    virtual void Scenes        (void) ;
    virtual void StopScenes    (void) ;

    virtual void NewWorld      (void) ;
    virtual void FullWorld     (void) ;

    virtual void Gallery       (bool enabled) ;

  protected slots:

    virtual void Start         (void) ;

  private slots:

    void         ShowMonitors  (void) ;
    void         ShowWindows   (void) ;

  signals:

    void         EmitStart     (void) ;

} ;

#endif // ICPT_HPP
