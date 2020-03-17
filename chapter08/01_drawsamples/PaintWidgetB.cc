#include "PaintWidgetB.h"

PaintWidgetB::PaintWidgetB(QWidget *parent)
  :QWidget(parent)
{
}

void PaintWidgetB::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setPen(QPen(Qt::black, 15, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
  painter.setBrush(QBrush(Qt::blue, Qt::DiagCrossPattern));
  painter.drawPie(10, 10, 320, 200, 60*16, 270*16);
}
