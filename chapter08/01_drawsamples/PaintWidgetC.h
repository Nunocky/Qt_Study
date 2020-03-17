#ifndef PAINTWIDGETC_H
#define PAINTWIDGETC_H

#include <QtGui>
#include <QtWidgets>

class PaintWidgetC: public QWidget
{
  Q_OBJECT

public:

  PaintWidgetC(QWidget *parent=0);

protected:
  void paintEvent(QPaintEvent *event);
  
};


#endif
