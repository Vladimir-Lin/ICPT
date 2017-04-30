#ifndef SHOWCURVES_HPP
#define SHOWCURVES_HPP

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glaux.h>
//#include <GL/glext.h>

#include "Linear.hpp"
#include "Catastrophe.hpp"
#include "Physics.hpp"
#include "System.hpp"

class ShowCurves : public    QOpenGLWidget
                 , protected QOpenGLFunctions
                 , public    CA::Thread
{
  Q_OBJECT
  public:

    explicit      ShowCurves     (QWidget * parent = NULL) ;
    virtual      ~ShowCurves     (void) ;

    virtual QSize sizeHint       (void) const ;

  protected:

    QTimer      TTT ;
    CA::Vector4 V4  ;

    void          initializeGL   (void) ;
    void          paintGL        (void) ;
    void          resizeGL       (int width,int height) ;

  private:

    bool          bindError      (void) ;
    bool          BindTexture    (QImage * image,GLuint & id) ;
    void          PushPoints     (int n,int gaps,double * points) ;

  public slots:

    void          StartTime      (void) ;
    void          StopTime       (void) ;

    void          FlushGL        (void) ;
    void          Intervals      (void) ;

  protected slots:

    void          DrawCurves     (void) ;

  private slots:

  signals:

} ;

#endif // SHOWCURVES_HPP
