#include "PaintWidgetA.h"

PaintWidgetA::PaintWidgetA(QWidget *parent)
  :QWidget(parent)
{
}

void PaintWidgetA::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
  painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
  painter.drawEllipse(10, 10, 200, 120);
}
