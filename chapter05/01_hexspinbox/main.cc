#include <QApplication>

#include "hexspinbox.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  HexSpinBox spinbox;
  spinbox.show();
  
  return app.exec();
}
