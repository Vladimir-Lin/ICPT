#include "ShowCurves.hpp"

MenuManager:: MenuManager(QWidget * widget)
{
  menu  = new QMenu    ( widget                           ) ;
  menu -> setAttribute ( Qt::WA_InputMethodEnabled , true ) ;
}

MenuManager::~MenuManager(void)
{
  menu -> deleteLater ( ) ;
  menu  = NULL            ;
}

QAction * MenuManager::exec(QPoint pos)
{
  if ( actions . count ( ) <= 0 ) return NULL ;
  return menu -> exec ( pos )                 ;
}

QAction * MenuManager::add(int Id,QString text)
{
  QAction   * a = menu -> addAction ( text ) ;
  actions  << a                              ;
  IDs [ a ] = Id                             ;
  return a                                   ;
}

QAction * MenuManager::add(int Id,QIcon icon,QString text)
{
  QAction   * a = menu -> addAction ( icon , text ) ;
  actions  << a                                     ;
  IDs [ a ] = Id                                    ;
  return a                                          ;
}

QAction * MenuManager::add(int Id,QString text,bool checkable,bool checked)
{
  QAction   * a = menu -> addAction ( text ) ;
  actions  << a                              ;
  IDs [ a ] = Id                             ;
  a -> setCheckable ( checkable )            ;
  a -> setChecked   ( checked   )            ;
  return a                                   ;
}

QAction * MenuManager::add(int Id,QIcon icon,QString text,bool checkable,bool checked)
{
  QAction   * a = menu -> addAction ( icon , text ) ;
  actions  << a                                     ;
  IDs [ a ] = Id                                    ;
  a -> setCheckable ( checkable )                   ;
  a -> setChecked   ( checked   )                   ;
  return a                                          ;
}

QAction * MenuManager::addSeparator (void)
{
  return menu -> addSeparator ( ) ;
}

QMenu * MenuManager::addMenu(QString title)
{
  QMenu * m = menu -> addMenu( title ) ;
  menus << m                           ;
  return  m                            ;
}

QMenu * MenuManager::addMenu(QMenu * m,QString title)
{
  QMenu * n = m -> addMenu( title ) ;
  menus << n                        ;
  return  n                         ;
}

QAction * MenuManager::add(QMenu * m,int Id,QString text)
{
  QAction  * a = m -> addAction ( text ) ;
  actions << a                           ;
  IDs [ a ]   = Id                       ;
  return a                               ;
}

QAction * MenuManager::add(QMenu * m,int Id,QIcon icon,QString text)
{
  QAction  * a = m -> addAction ( icon , text ) ;
  actions << a                                  ;
  IDs [ a ]   = Id                              ;
  return a                                      ;
}

QAction * MenuManager::add(QMenu * m,int Id,QString text,bool checkable,bool checked)
{
  QAction   * a = m -> addAction ( text ) ;
  actions  << a                           ;
  IDs [ a ] = Id                          ;
  a -> setCheckable ( checkable )         ;
  a -> setChecked   ( checked   )         ;
  return a                                ;
}

QAction * MenuManager::add(QMenu * m,int Id,QIcon icon,QString text,bool checkable,bool checked)
{
  QAction   * a = m -> addAction ( icon , text ) ;
  actions  << a                                  ;
  IDs [ a ] = Id                                 ;
  a -> setCheckable ( checkable )                ;
  a -> setChecked   ( checked   )                ;
  return a                                       ;
}

QAction * MenuManager::addSeparator(QMenu * m)
{
  return m -> addSeparator ( ) ;
}

QAction * MenuManager::add(int Id,QWidget * W)
{
  QWidgetAction * widgetAction = new QWidgetAction ( menu->parentWidget() ) ;
  widgetAction -> setDefaultWidget ( W )                                    ;
  QAction       * a            = (QAction *) widgetAction                   ;
  menu     -> addAction ( a )                                               ;
  actions  << a                                                             ;
  IDs     [  a ] = Id                                                       ;
  Widgets [ Id ] = W                                                        ;
  return a                                                                  ;
}

QAction * MenuManager::add(QMenu * m,int Id,QWidget * W)
{
  QWidgetAction * widgetAction = new QWidgetAction ( menu->parentWidget() ) ;
  widgetAction->setDefaultWidget(W)                                         ;
  QAction       * a            = (QAction *) widgetAction                   ;
  m        -> addAction ( a )                                               ;
  actions  << a                                                             ;
  IDs     [ a  ] = Id                                                       ;
  Widgets [ Id ] = W                                                        ;
  return a                                                                  ;
}

bool MenuManager::contains(QAction * action)
{
  if ( NULL == action ) return false   ;
  return actions . contains ( action ) ;
}

int MenuManager::operator [ ] (QAction * action)
{
  if ( ! IDs . contains ( action ) ) return -1 ;
  return IDs [ action ]                        ;
}

void MenuManager::setFont(QFont font)
{
  menu -> setFont ( font )                       ;
  for (int i = 0 ; i < menus . count ( ) ; i++ ) {
    menus [ i ] -> setFont ( font )              ;
  }                                              ;
}

QActionGroup * MenuManager::group(int Id)
{
  if ( ! actionGroups . contains ( Id ) ) return NULL ;
  return actionGroups [ Id ]                          ;
}

int MenuManager::setGroup(int Id,QActionGroup * group)
{
  actionGroups [ Id ]  = group ;
  return Id                    ;
}

QWidget * MenuManager::widget(int Id)
{
  if ( ! Widgets . contains ( Id ) ) return NULL ;
  return Widgets [ Id ]                          ;
}
