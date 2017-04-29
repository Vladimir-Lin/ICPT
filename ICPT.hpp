#ifndef ICPT_HPP
#define ICPT_HPP

#include <QMainWindow>

namespace Ui {
  class ICPT;
}

class ICPT : public QMainWindow
{
  Q_OBJECT

public:
  explicit ICPT(QWidget *parent = 0);
  ~ICPT();

private:
  Ui::ICPT *ui;
};

#endif // ICPT_HPP
