#include "ShowCurves.hpp"

GalleryView:: GalleryView ( QWidget * parent )
            : QListWidget (           parent )
{
  setWindowTitle ( tr("Gallery") ) ;
}

GalleryView::~GalleryView (void)
{
}

QSize GalleryView::sizeHint(void) const
{
  return QSize ( 640 , 480 ) ;
}
