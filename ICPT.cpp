#include "ICPT.hpp"
#include "ui_ICPT.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ICPT w;
  w.show();

  return a.exec();
}

ICPT::ICPT(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ICPT)
{
  ui->setupUi(this);
}

ICPT::~ICPT()
{
  delete ui;
}
