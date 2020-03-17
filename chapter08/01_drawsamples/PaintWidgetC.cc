#include "PaintWidgetC.h"

PaintWidgetC::PaintWidgetC(QWidget *parent)
  :QWidget(parent)
{
}

void PaintWidgetC::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setPen(QPen(Qt::black, 15, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));

  QPainterPath path;
  path.moveTo(80, 200);
  path.cubicTo(120, 10, 150, 10, 320, 240);
  painter.setPen(QPen(Qt::black, 8));
  painter.drawPath(path);
}
