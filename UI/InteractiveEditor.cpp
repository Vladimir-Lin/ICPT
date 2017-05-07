#include "ShowCurves.hpp"

InteractiveEditor:: InteractiveEditor ( QWidget * widget )
                  : QWidget           (           widget )
                  , cursorTimer       ( NULL             )
                  , scrollArea        ( NULL             )
{
  QScrollArea * sa = NULL                               ;
  sa = qobject_cast<QScrollArea *> ( parentWidget ( ) ) ;
  if ( NULL != sa ) Join ( sa )                         ;
  Configure ( )                                         ;
}

InteractiveEditor::~InteractiveEditor (void)
{
  shutdown ( ) ;
}

void InteractiveEditor::Join(QScrollArea * area)
{
  if ( NULL == area ) return                                         ;
  scrollArea  = area                                                 ;
  scrollArea -> setWidget                  ( this                  ) ;
  scrollArea -> setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOn ) ;
  scrollArea -> setWidgetResizable         ( true                  ) ;
  scrollArea -> setFocusPolicy             ( Qt::NoFocus           ) ;
}

void InteractiveEditor::Configure(void)
{
  setAttribute                    ( Qt::WA_InputMethodEnabled )        ;
  //////////////////////////////////////////////////////////////////////
  Prompt        = ">: "                                                ;
  PrevRect      . setRect                  ( 0 , 0 , 0 , 0    )        ;
  blink         = false                                                ;
  overwriteMode = false                                                ;
  charWidth     = fontMetrics ( ) . width  ( QLatin1Char('9') )        ;
  charHeight    = fontMetrics ( ) . height (                  )        ;
  cursorX       = fontMetrics ( ) . width  ( Prompt           )        ;
  cursorY       = 0                                                    ;
  HistoryIndex  = -1                                                   ;
  //////////////////////////////////////////////////////////////////////
  Symbols << " "  ; Symbols << "."  ; Symbols << "_"  ; Symbols << "=" ;
  Symbols << "+"  ; Symbols << "-"  ; Symbols << "*"  ; Symbols << "/" ;
  Symbols << "&"  ; Symbols << "^"  ; Symbols << "%"  ; Symbols << "!" ;
  Symbols << "|"  ; Symbols << ":"  ; Symbols << ";"  ; Symbols << "," ;
  Symbols << "`"  ; Symbols << "["  ; Symbols << "]"  ; Symbols << "(" ;
  Symbols << ")"  ; Symbols << "{"  ; Symbols << "}"  ; Symbols << "<" ;
  Symbols << ">"  ; Symbols << "\"" ; Symbols << "'"  ; Symbols << "#" ;
  Symbols << "@"  ; Symbols << "$"  ; Symbols << ","  ; Symbols << "?" ;
  //////////////////////////////////////////////////////////////////////
  setFocusPolicy   ( Qt::WheelFocus                                  ) ;
  QObject::connect ( this , SIGNAL ( EmitUpdate   ( ) )                ,
                     this , SLOT   ( update       ( ) )              ) ;
  startCursor      (                                                 ) ;
}

void InteractiveEditor::contextMenuEvent(QContextMenuEvent * e)
{
  if ( Menu ( e -> pos ( ) ) )      {
    e -> accept ( )                 ;
  } else                            {
    QWidget::contextMenuEvent ( e ) ;
  }                                 ;
}

void InteractiveEditor::focusInEvent(QFocusEvent * e)
{
  if ( e -> gotFocus ( ) )       {
    e -> accept ( )              ;
  } else                         {
    QWidget::focusInEvent  ( e ) ;
  }
}

void InteractiveEditor::focusOutEvent(QFocusEvent * e)
{
  if ( e -> lostFocus ( ) )      {
    e -> accept ( )              ;
  } else                         {
    QWidget::focusOutEvent ( e ) ;
  }                              ;
}

void InteractiveEditor::resizeEvent(QResizeEvent * e)
{
  QWidget::resizeEvent ( e ) ;
}

void InteractiveEditor::showEvent(QShowEvent * e)
{
  QWidget::showEvent   ( e ) ;
}

void InteractiveEditor::keyPressEvent(QKeyEvent * e)
{
  QString t  = e -> text ( )                                             ;
  bool    kp = false                                                     ;
  int     key                                                            ;
  if ( t . length ( ) <= 0 ) kp = true                                   ;
  ////////////////////////////////////////////////////////////////////////
  if ( e -> key ( ) == Qt::Key_Enter || e -> key ( ) == Qt::Key_Return ) {
    Enter  ( )                                                           ;
    Adjust ( )                                                           ;
    return                                                               ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if ( e -> key ( ) == Qt::Key_Up )                                      {
    GoUp   ( )                                                           ;
    Adjust ( )                                                           ;
    return                                                               ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if ( e -> key ( ) == Qt::Key_Down )                                    {
    GoDown ( )                                                           ;
    Adjust ( )                                                           ;
    return                                                               ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if ( ( e -> key       ( ) == Qt::Key_Backspace )                      &&
       ( e -> modifiers ( ) == Qt::NoModifier    )                     ) {
    int len = Commands . length (     )                                  ;
    len = len - 1                                                        ;
    if (len<0) len = 0                                                   ;
    Commands = Commands . left  ( len )                                  ;
    Adjust                      (     )                                  ;
    return                                                               ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if (!kp)                                                               {
    key = t.at(0).toLatin1()                                             ;
    if (key>='a' && key<='z')                                            {
      Commands . append ( key )                                          ;
      Evaluate          (     )                                          ;
      Adjust            (     )                                          ;
      return                                                             ;
    }                                                                    ;
    if (key>='A' && key<='Z')                                            {
      Commands . append ( key )                                          ;
      Evaluate          (     )                                          ;
      Adjust            (     )                                          ;
      return                                                             ;
    }                                                                    ;
    if ( ( key >= '0' ) && ( key <= '9' ) )                              {
      Commands . append ( key )                                          ;
      Evaluate          (     )                                          ;
      Adjust            (     )                                          ;
      return                                                             ;
    }                                                                    ;
    if ( Symbols . contains ( QChar ( key ) ) )                          {
      Commands . append ( key )                                          ;
      Evaluate          (     )                                          ;
      Adjust            (     )                                          ;
      return                                                             ;
    }                                                                    ;
    kp = true                                                            ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  if ( kp ) QWidget::keyPressEvent ( e )                                 ;
  ////////////////////////////////////////////////////////////////////////
  emit EmitUpdate ( )                                                    ;
}

void InteractiveEditor::inputMethodEvent(QInputMethodEvent * e)
{
  if ( InsertIM ( e -> commitString ( ) , e -> preeditString ( ) ) ) {
    e -> accept ( )                                                  ;
    return                                                           ;
  }                                                                  ;
  QWidget :: inputMethodEvent ( e )                                  ;
}

QVariant InteractiveEditor::inputMethodQuery(Qt::InputMethodQuery query) const
{
  switch ( query )                                        {
    case Qt::ImCursorRectangle                            :
    return QVariant ( QRect  ( cursorX   , cursorY        ,
                               charWidth , charHeight ) ) ;
    case Qt::ImFont                                       :
    return font ( )                                       ;
    case Qt::ImCursorPosition                             :
    return QVariant ( QPoint ( cursorX , cursorY )      ) ;
    case Qt::ImSurroundingText                            :
    return QVariant ( imString )                          ;
    case Qt::ImCurrentSelection                           :
    return QVariant ( peString )                          ;
    case Qt::ImMaximumTextLength                          :
    return QVariant ( 512 )                               ;
    case Qt::ImAnchorPosition                             :
    case Qt::ImEnabled                                    :
    case Qt::ImHints                                      :
    case Qt::ImPreferredLanguage                          :
    case Qt::ImPlatformData                               :
    case Qt::ImAbsolutePosition                           :
    case Qt::ImTextBeforeCursor                           :
    case Qt::ImTextAfterCursor                            :
    default                                               :
    return QWidget::inputMethodQuery ( query )            ;
  }                                                       ;
}

bool InteractiveEditor::InsertIM(QString commit,QString preedit)
{
  if ( commit . length ( ) > 0 )      {
    Commands = imString + commit      ;
    imString = ""                     ;
    peString = ""                     ;
    Evaluate ( )                      ;
    Adjust   ( )                      ;
    return true                       ;
  } else
  if ( preedit . length ( ) > 0 )     {
    if ( imString . length ( ) <= 0 ) {
      imString = Commands             ;
    }                                 ;
    peString = preedit                ;
    Commands = imString + preedit     ;
    Evaluate ( )                      ;
    Adjust   ( )                      ;
    return false                      ;
  } else                              {
    imString = Commands               ;
  }                                   ;
  return true                         ;
}

void InteractiveEditor::mouseMoveEvent(QMouseEvent * e)
{
  emit EmitUpdate ( ) ;
}

void InteractiveEditor::mousePressEvent(QMouseEvent * e)
{
  if ( Qt::LeftButton == ( e -> buttons ( ) & Qt::LeftButton ) ) {
    emit EmitUpdate ( )                                          ;
  } else                                                         {
    QWidget::mousePressEvent ( e )                               ;
  }                                                              ;
}

void InteractiveEditor::closeEvent(QCloseEvent * e)
{
  if ( shutdown ( ) ) e -> accept ( ) ; else
  QWidget::closeEvent ( e )                ;
}

void InteractiveEditor::paintCursor(QPainter & painter)
{
  if ( ! hasFocus ( ) ) return                       ;
  if ( ! blink        ) return                       ;
  if ( overwriteMode  )                              {
    painter . fillRect                               (
      cursorX                                        ,
      cursorY + charHeight - 2                       ,
      charWidth                                      ,
      2                                              ,
      palette ( ) . color ( QPalette::WindowText ) ) ;
  } else                                             {
    painter . fillRect                               (
      cursorX                                        ,
      cursorY                                        ,
      2                                              ,
      charHeight                                     ,
      palette ( ) . color ( QPalette::WindowText ) ) ;
  }                                                  ;
}

void InteractiveEditor::paintContents(QPainter & p)
{
  QString     H = QString::fromUtf8 ( History )                 ;
  QStringList L = H . split         ( '\n'    )                 ;
  if ( History . size ( ) <= 0 ) L . clear ( )                  ;
  L << QString ( "%1%2" ) . arg ( Prompt ) . arg ( Commands )   ;
  QString T = L . join ( "\n" )                                 ;
  QRect R      ( 0 , 0 , width ( ) , height ( )               ) ;
  p . setPen   ( palette ( ) . color ( QPalette::WindowText ) ) ;
  p . drawText ( R , Qt::AlignLeft | Qt::AlignTop , T         ) ;
}

void InteractiveEditor::paintEvent(QPaintEvent * e)
{
  QPainter p    ( this                                                   ) ;
  p . fillRect  ( e -> rect ( ) , palette ( ) . color ( QPalette::Base ) ) ;
  paintContents ( p                                                      ) ;
  paintCursor   ( p                                                      ) ;
}

void InteractiveEditor::updateCursor(void)
{
  blink = blink ? false : true                          ;
  update ( cursorX , cursorY , charWidth , charHeight ) ;
}

int InteractiveEditor::cursorAt(QString L)
{
  QRect T = fontMetrics().boundingRect(L)                  ;
  QString E                                                ;
  if (T.width()<width()) return T.width()                  ;
  do                                                       {
    int s,l,n                                              ;
    bool g = false                                         ;
    E = fontMetrics().elidedText(L,Qt::ElideRight,width()) ;
    s = E.length() - 3                                     ;
    l = s + 1                                              ;
    n = L.length()                                         ;
    for (int i=s;!g && i<n;i++,s++,l++)                    {
      QString M = L.left(l)                                ;
      T = fontMetrics().boundingRect(M)                    ;
      if (T.width()>width()) g = true                      ;
    }                                                      ;
    if (g) L = L.mid(l)                                    ;
    T = fontMetrics().boundingRect(L)                      ;
  } while (T.width()>width())                              ;
  return 0                                                 ;
}

void InteractiveEditor::Adjust(void)
{
  QString     H = QString::fromUtf8(History)               ;
  QStringList L = H . split ( '\n' )                       ;
  QRect       G                                            ;
  if ( NULL != scrollArea )                                {
    G = scrollArea -> geometry ( )                         ;
  } else                                                   {
    G = geometry               ( )                         ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  QRect   M =               geometry ( )                   ;
  int     C = L           . count    ( )                   ;
  int     A = Qt::AlignLeft|Qt::AlignTop                   ;
  QString T                                                ;
  QString I                                                ;
  QRect   F                                                ;
  //////////////////////////////////////////////////////////
  I = QString("%1%2").arg(Prompt).arg(Commands)            ;
  if (History.size()<=0) L . clear ( )                     ;
  charWidth  = fontMetrics() . width  ( QLatin1Char('9') ) ;
  charHeight = fontMetrics() . height (                  ) ;
  L << I                                                   ;
  T  = L.join("\n")                                        ;
  C  = 4 * ( C + 1 )                                       ;
  C *= charHeight                                          ;
  F  . setRect(0,0,M.width(),C)                            ;
  F  = fontMetrics().boundingRect(F,A,T)                   ;
  if (F.height()>G.height())                               {
    M.setRect(0,0,M.width(),F.height())                    ;
  } else                                                   {
    M.setRect(0,0,M.width(),G.height() - 6)                ;
  }                                                        ;
  if (M!=PrevRect)                                         {
    setMinimumHeight ( M.height() )                        ;
    PrevRect = M                                           ;
  }                                                        ;
  cursorY = F.height() - charHeight                        ;
  cursorX = cursorAt(I)                                    ;
  emit EmitUpdate ( )                                      ;
  ensureVisible   ( )                                      ;
}

void InteractiveEditor::ensureVisible(void)
{
  if ( NULL != scrollArea ) return ;
  scrollArea -> ensureVisible      (
    cursorX                        ,
    cursorY + charHeight/2         ,
    3                              ,
    charHeight/2 + 2             ) ;
}

void InteractiveEditor::Evaluate(void)
{
  QString     C = Commands            ;
  QString     c = C . toLower (     ) ;
  QStringList h = c . split   ( ' ' ) ;
  QStringList m                       ;
  if ( h . count ( ) <= 0 ) return    ;
  int l = h [ 0 ] . length ( )        ;
  if ( l             <= 0 ) return    ;
  if ( m . count ( ) <= 0 ) return    ;
  if ( ! isToolTip        ) return    ;
}

QStringList InteractiveEditor::Split(QString c)
{
  QStringList h = c . split ( ' ' )  ;
  QStringList H                      ;
  QString     s                      ;
  foreach ( s , h )                  {
    if ( s . length ( ) > 0 ) H << s ;
  }                                  ;
  return H                           ;
}

bool InteractiveEditor::Menu(QPoint pos)
{
  MenuManager mm  ( this                         ) ;
  QAction   * aa                                   ;
  mm . add        ( 101 , tr ( "Clear history" ) ) ;
  mm . add        ( 102 , tr ( "Clear command" ) ) ;
  mm . add        ( 301 , tr ( "Append files"  ) ) ;
  //////////////////////////////////////////////////
  mm . setFont    ( font ( )                     ) ;
  aa = mm . exec  (                              ) ;
  //////////////////////////////////////////////////
  if ( NULL == aa ) return true                    ;
  //////////////////////////////////////////////////
  switch          ( mm [ aa ]                    ) {
    case 101                                       :
      Clear       (                              ) ;
    break                                          ;
    case 102                                       :
      Commands = ""                                ;
      Adjust      (                              ) ;
    break                                          ;
    case 301                                       :
      BrowseFiles (                              ) ;
    break                                          ;
  }                                                ;
  //////////////////////////////////////////////////
  return true                                      ;
}

void InteractiveEditor::setFont(void)
{
  changeFont               ( )                               ;
  charWidth  = fontMetrics ( ) . width  ( QLatin1Char('9') ) ;
  charHeight = fontMetrics ( ) . height (                  ) ;
}

bool InteractiveEditor::changeFont(void)
{
  bool  okay = false                     ;
  QFont f    = font        (           ) ;
  f = QFontDialog::getFont ( &okay , f ) ;
  if ( ! okay ) return false             ;
  QWidget::setFont         ( f         ) ;
  return true                            ;
}

void InteractiveEditor::Clear(void)
{
  History . clear ( ) ;
  Adjust          ( ) ;
}

QStringList & InteractiveEditor::CommandQueue(void)
{
  return Queues ;
}

void InteractiveEditor::Report(QString message)
{
  if ( message . length ( ) <= 0 ) return ;
  QByteArray U = message . toUtf8 ( )     ;
  History . append ( U )                  ;
  Adjust           (   )                  ;
}

bool InteractiveEditor::startCursor(void)
{
  if ( NULL == cursorTimer )                        {
    cursorTimer = new QTimer ( this )               ;
    QObject::connect( cursorTimer                   ,
                      SIGNAL ( timeout      ( ) )   ,
                      this                          ,
                      SLOT   ( updateCursor ( ) ) ) ;
  }                                                 ;
  cursorTimer -> start ( 500 )                      ;
  return true                                       ;
}

bool InteractiveEditor::shutdown(void)
{
  if ( NULL != cursorTimer )  {
    QTimer * E  = cursorTimer ;
    cursorTimer = NULL        ;
    E -> stop        ( )      ;
    E -> deleteLater ( )      ;
  }                           ;
  return true                 ;
}

void InteractiveEditor::Copy(void)
{
  QString     H = QString::fromUtf8 ( History )               ;
  QStringList L = H . split ( '\n' )                          ;
  L << QString ( "%1%2" ) . arg ( Prompt ) . arg ( Commands ) ;
  QString     T = L . join  ( "\n" )                          ;
  qApp -> clipboard ( ) -> setText ( T )                      ;
}

void InteractiveEditor::Paste(void)
{
  QString T = qApp -> clipboard ( ) -> text ( ) ;
  if ( T . length ( ) <= 0 ) return             ;
  Commands . append ( T )                       ;
  Evaluate          (   )                       ;
  Adjust            (   )                       ;
  emit EmitUpdate   (   )                       ;
}

void InteractiveEditor::GoUp(void)
{
  HistoryIndex ++                                ;
  if ( HistoryIndex >= CommandList . count ( ) ) {
    HistoryIndex --                              ;
    return                                       ;
  }                                              ;
  Commands = CommandList [ HistoryIndex ]        ;
}

void InteractiveEditor::GoDown(void)
{
  if ( HistoryIndex <= 0 ) return                       ;
  HistoryIndex --                                       ;
  if ( HistoryIndex >= CommandList . count ( ) ) return ;
  Commands = CommandList [ HistoryIndex ]               ;
}

void InteractiveEditor::setPrompt(QString prompt)
{
  Prompt = prompt ;
}

void InteractiveEditor::Enter(void)
{
  if ( Commands . length ( ) <= 0 ) return ;
  Report ( Commands )                      ;
  Report ( "\n"     )                      ;
  Queues  << Commands                      ;
  Commands = ""                            ;
  emit LineInput ( )                       ;
}

void InteractiveEditor::Enter(QString command)
{
  if ( command . length ( ) <= 0 ) return ;
  Report         ( command )              ;
  Report         ( "\n"    )              ;
  Queues  << command                      ;
  emit LineInput (         )              ;
}

void InteractiveEditor::BrowseFiles(void)
{
  QStringList s                     ;
  s = QFileDialog::getOpenFileNames (
        this                        ,
        tr("Browse files")          ,
        ""                          ,
        tr("All files (*.*)")     ) ;
  if ( s . count ( ) <= 0 ) return  ;
  QStringList x                     ;
  QString     l                     ;
  foreach ( l , s )                 {
    l . prepend ( "\"" )            ;
    l . append  ( "\"" )            ;
    x << l                          ;
  }                                 ;
  l = x . join ( " " )              ;
  if ( Commands . length ( ) > 0 )  {
    l . prepend ( " " )             ;
  }                                 ;
  Commands . append ( l )           ;
  Adjust            (   )           ;
}

void InteractiveEditor::ClearCommands(void)
{
  CommandList . clear ( ) ;
}

bool InteractiveEditor::LoadCommands(QString filename)
{
  QFileInfo FXI              ( filename        ) ;
  if ( ! FXI . exists ( ) ) return false         ;
  QStringList L = StringList ( filename , "\n" ) ;
  L = PurifyLines            ( L               ) ;
  if ( L . count ( ) <= 0 ) return false         ;
  CommandList = L                                ;
  return true                                    ;
}

bool InteractiveEditor::SaveCommands(QString filename)
{
  if ( CommandList . count ( ) <= 0 ) return false   ;
  QString    S = CommandList . join ( "\r\n"       ) ;
  QByteArray B = S . toUtf8         (              ) ;
  return toFile                     ( filename , B ) ;
}

bool InteractiveEditor::toByteArray(QString filename,QByteArray & Body)
{
  QFile F ( filename )                                   ;
  if ( ! F . open ( QIODevice::ReadOnly ) ) return false ;
  Body = F . readAll ( )                                 ;
  F        . close   ( )                                 ;
  return ( Body . size ( ) > 0 )                         ;
}

bool InteractiveEditor::toFile(QString filename,QByteArray & Body)
{
  QFile F ( filename )                                    ;
  if ( ! F . open ( QIODevice::WriteOnly ) ) return false ;
  qint64 size = F . write ( Body )                        ;
  F . close   ( )                                         ;
  return ( Body . size ( ) == size )                      ;
}

QStringList InteractiveEditor::StringList(QString filename,QString split)
{
  QStringList s                                     ;
  QString     b                                     ;
  QByteArray  Body                                  ;
  if ( ! toByteArray ( filename , Body ) ) return s ;
  b = QString::fromUtf8 ( Body )                    ;
  s = b . split ( split )                           ;
  return s                                          ;
}

QStringList InteractiveEditor::PurifyLines(QStringList lines)
{
  QStringList s                     ;
  for (int i=0;i<lines.count();i++) {
    QString l = lines[i]            ;
    l = l . replace ( "\n" , "" )   ;
    l = l . replace ( "\r" , "" )   ;
    s << l                          ;
  }                                 ;
  return s                          ;
}
