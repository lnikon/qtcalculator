#include "calculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Calculator   w;

  w.setWindowTitle("CalcIT!");
  w.setMinimumSize(300, 400);
  w.show();

  return a.exec();
}
