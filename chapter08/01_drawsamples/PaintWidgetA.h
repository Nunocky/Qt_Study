#ifndef PAINTWIDGETA_H
#define PAINTWIDGETA_H

#include <QtGui>
#include <QtWidgets>

class PaintWidgetA: public QWidget
{
  Q_OBJECT

public:

  PaintWidgetA(QWidget *parent=0);

protected:
  void paintEvent(QPaintEvent *event);
  
};


#endif
