#ifndef PAINTWIDGETB_H
#define PAINTWIDGETB_H

#include <QtGui>
#include <QtWidgets>

class PaintWidgetB: public QWidget
{
  Q_OBJECT

public:

  PaintWidgetB(QWidget *parent=0);

protected:
  void paintEvent(QPaintEvent *event);
  
};


#endif
