#include <QtGui>
#include <QtWidgets>

#include "MyTableWidget.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  MyTableWidget *tbl = new MyTableWidget();

  tbl->show();



  return app.exec();
}
