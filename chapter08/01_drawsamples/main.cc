#include <QtGui>
#include <QtWidgets>



#include "PaintWidgetA.h"
#include "PaintWidgetB.h"
#include "PaintWidgetC.h"



int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  QWidget *window = new QWidget;
  QHBoxLayout *mainLayout = new QHBoxLayout();

  PaintWidgetA *pA = new PaintWidgetA();
  pA->setMinimumSize(320, 240);

  PaintWidgetB *pB = new PaintWidgetB();
  pB->setMinimumSize(320, 240);

  PaintWidgetC *pC = new PaintWidgetC();
  pC->setMinimumSize(320, 240);

  mainLayout->addWidget(pA);
  mainLayout->addWidget(pB);
  mainLayout->addWidget(pC);
  
  window->setLayout(mainLayout);

  window->show();

  return app.exec();
}
