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
#include "Graphics.hpp"

class MenuManager
{
  public:

    QMenu * menu ;

    explicit       MenuManager  (QWidget * widget) ;
    virtual       ~MenuManager  (void);

    QAction      * exec         (QPoint pos = QCursor::pos()) ;

    QAction      * add          (int Id,QString text);
    QAction      * add          (int Id,QIcon icon,QString text);
    QAction      * add          (int Id,QString text,bool checkable,bool checked);
    QAction      * add          (int Id,QIcon icon,QString text,bool checkable,bool checked);
    QAction      * addSeparator (void) ;

    QMenu        * addMenu      (QString title) ;
    QMenu        * addMenu      (QMenu * m,QString title) ;
    QAction      * add          (QMenu * m,int Id,QString text);
    QAction      * add          (QMenu * m,int Id,QIcon icon,QString text);
    QAction      * add          (QMenu * m,int Id,QString text,bool checkable,bool checked);
    QAction      * add          (QMenu * m,int Id,QIcon icon,QString text,bool checkable,bool checked);
    QAction      * addSeparator (QMenu * m) ;

    QAction      * add          (int Id,QWidget * widget) ;
    QAction      * add          (QMenu * m,int Id,QWidget * widget) ;

    bool           contains     (QAction * action) ;
    int            operator [ ] (QAction * action) ;

    void           setFont      (QFont  font) ;

    QActionGroup * group        (int Id) ;
    int            setGroup     (int Id,QActionGroup * group) ;

    QWidget      * widget       (int Id) ;

  protected:

    QList<QAction *                > actions      ;
    QList<QMenu   *                > menus        ;
    QMap <QAction *, int           > IDs          ;
    QMap <int      , QWidget      *> Widgets      ;
    QMap <int      , QActionGroup *> actionGroups ;

  private:

} ;

class InteractiveEditor : public QWidget
{
  Q_OBJECT
  public:

    QScrollArea * scrollArea ;

    explicit InteractiveEditor        (QWidget * widget) ;
    virtual ~InteractiveEditor        (void) ;

    virtual void  Join                (QScrollArea * area) ;
    virtual void  Report              (QString message) ;
    virtual void  Clear               (void) ;

    QStringList & CommandQueue        (void) ;

    bool          toFile              (QString filename,QByteArray & Body) ;
    bool          toByteArray         (QString filename,QByteArray & Body) ;

    QStringList   StringList          (QString filename,QString split) ;
    QStringList   PurifyLines         (QStringList lines) ;

  protected:

    QByteArray  History       ;
    QStringList Symbols       ;
    QStringList Queues        ;
    QStringList CommandList   ;
    QString     Prompt        ;
    QString     Commands      ;
    QString     imString      ;
    QString     peString      ;
    QTimer    * cursorTimer   ;
    QRect       PrevRect      ;
    bool        blink         ;
    bool        overwriteMode ;
    bool        isToolTip     ;
    int         charWidth     ;
    int         charHeight    ;
    int         cursorX       ;
    int         cursorY       ;
    int         Mode          ;
    int         Verbose       ;
    int         HistoryIndex  ;
    LMAPs       States        ;

    virtual void Configure            (void) ;

    virtual void contextMenuEvent     (QContextMenuEvent  * event) ;
    virtual void focusInEvent         (QFocusEvent        * event) ;
    virtual void focusOutEvent        (QFocusEvent        * event) ;
    virtual void resizeEvent          (QResizeEvent       * event) ;
    virtual void showEvent            (QShowEvent         * event) ;
    virtual void keyPressEvent        (QKeyEvent          * event) ;
    virtual void mouseMoveEvent       (QMouseEvent        * event) ;
    virtual void mousePressEvent      (QMouseEvent        * event) ;
    virtual void paintEvent           (QPaintEvent        * event) ;
    virtual void closeEvent           (QCloseEvent        * event) ;

    virtual void inputMethodEvent     (QInputMethodEvent  * event) ;
    virtual QVariant inputMethodQuery (Qt::InputMethodQuery query) const ;
    virtual bool InsertIM             (QString commit,QString preedit) ;

    virtual void paintCursor          (QPainter & painter) ;
    virtual void paintContents        (QPainter & painter) ;

  private:

    int          cursorAt             (QString L) ;
    bool         canDo                (QString value) ;
    QStringList  Split                (QString command) ;
    bool         changeFont           (void) ;

  public slots:

    virtual bool startCursor          (void) ;
    virtual bool shutdown             (void) ;
    virtual void Adjust               (void) ;
    virtual void ensureVisible        (void) ;
    virtual void Evaluate             (void) ;
    virtual void Enter                (void) ;
    virtual void Enter                (QString command) ;
    virtual void setFont              (void) ;
    virtual void Copy                 (void) ;
    virtual void Paste                (void) ;
    virtual void setPrompt            (QString prompt) ;
    virtual void BrowseFiles          (void) ;
    virtual void ClearCommands        (void) ;
    virtual bool LoadCommands         (QString filename) ;
    virtual bool SaveCommands         (QString filename) ;

  protected slots:

    virtual bool Menu                 (QPoint pos) ;

    virtual void GoUp                 (void) ;
    virtual void GoDown               (void) ;

    virtual void Parse                (QString command) ;

  private slots:

    void         updateCursor         (void) ;

  signals:

    void         EmitUpdate           (void) ;

} ;

class GalleryView : public QListWidget
{
  Q_OBJECT
  public:

    explicit      GalleryView (QWidget * parent = NULL) ;
    virtual      ~GalleryView (void) ;

    virtual QSize sizeHint    (void) const ;

  protected:

  private:

  public slots:

  protected slots:

  private slots:

  signals:

} ;

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

    QTimer      TTT    ;
    CA::Vector4 V4     ;
    CA::Camera  camera ;

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

class StarView : public    QOpenGLWidget
               , public    CA::Thread
               , protected QOpenGLFunctions
{
  Q_OBJECT
  public:

    explicit      StarView              (QWidget * parent = NULL) ;
    virtual      ~StarView              (void) ;

    virtual QSize sizeHint              (void) const ;

  protected:

    QTimer             TTT         ;
    CA::Vector4        V4          ;
    CA::Lights         lights      ;
    CA::Material       material    ;
    CA::Camera         camera      ;
    CA::Ball           Earth       ;
    CA::Position       Epp         ;
    CA::Ball           Moon        ;
    CA::Position       Mpp         ;
    CA::Ball           Sun         ;
    CA::Position       Spp         ;
    CA::Texture        Hoag        ;
    CA::Position       HoagPP      ;
    CA::Texture        Milky       ;
    CA::Position       MilkyPP     ;
    int                interval    ;
    bool               ggg         ;
    bool               rendering   ;
    bool               showup      ;
    double             cameraAngle ;
    double             zAngle      ;
    double           * esOrbit     ;
    double           * emOrbit     ;
    QList<CA::Vector4> EarthTail   ;
    QList<CA::Vector4> MoonTail    ;

    void          initializeGL          (void) ;
    void          paintGL               (void) ;
    void          resizeGL              (int width,int height) ;

    virtual void  mousePressEvent       (QMouseEvent * e) ;
    virtual void  mouseReleaseEvent     (QMouseEvent * e) ;
    virtual void  mouseDoubleClickEvent (QMouseEvent * e) ;
    virtual void  mouseMoveEvent        (QMouseEvent * e) ;

    virtual void  run                   (int Type,CA::ThreadData * Data) ;

    void          SolarSystem           (void) ;
    void          HoagObject            (void) ;
    void          HoagCompare           (void) ;

  private:

    void          BuildAll              (void) ;

    void          BuildEarth            (void) ;
    void          DeleteEarth           (void) ;
    void          DrawEarthOrbit        (void) ;

    void          BuildHoag             (void) ;
    void          DeleteHoag            (void) ;
    void          DrawHoag              (void) ;

    void          BuildMilky            (void) ;
    void          DeleteMilky           (void) ;
    void          DrawMilky             (void) ;

    bool          bindError             (void) ;
    void          PushPoints            (int n,int gaps,double * points) ;

    void          DrawTail              (CA::Vector4 Color,QList<CA::Vector4> & P) ;

  public slots:

    void          StartTime             (void) ;
    void          StopTime              (void) ;

    void          FlushGL               (void) ;
    void          Intervals             (void) ;

  protected slots:

  private slots:

  signals:

} ;

#endif // SHOWCURVES_HPP
