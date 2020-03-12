#include <QtGui>

#include "oventimer.h"

static const double DegreesPerMinute = 7.0;
static const double DegreesPerSecond = DegreesPerMinute / 60;
static const int    MaxMinutes       = 45;
static const int    MaxSeconds       = MaxMinutes * 60;
static const int    UpdateInterval   = 1;

OvenTimer::OvenTimer(QWidget *parent)
  : QWidget(parent)
{
  finishTime = QDateTime::currentDateTime();

  updateTimer = new QTimer(this);
  connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));

  finishTimer = new QTimer(this);
  finishTimer->setSingleShot(true);

  connect(finishTimer, SIGNAL(timeout()), this, SIGNAL(timeout()));
  connect(finishTimer, SIGNAL(timeout()), updateTimer, SLOT(stop()));
}

void
OvenTimer::setDuration(int secs)
{
  if (secs > MaxSeconds) {
    secs = MaxSeconds;
  }
  else if (secs <= 0) {
    secs = 0;
  }

  finishTime = QDateTime::currentDateTime().addSecs(secs);

  if (secs > 0) {
    updateTimer->start(UpdateInterval * 1000);
    finishTimer->start(secs * 1000);
  }
  else {
    updateTimer->stop();
    finishTimer->stop();
  }

  update();
}

int
OvenTimer::duration() const
{
  int secs = QDateTime::currentDateTime().secsTo(finishTime);
  if (secs < 0) {
    secs = 0;
  }

  return secs;
}

void
OvenTimer::draw(QPainter *painter)
{
  static const int triangles[3][2] = {
    {-2, -49},
    {2, -49},
    {0, -47}
  };

  QPen thickPen(palette().foreground(), 1.5);
  QPen thinPen(palette().foreground(), 0.5);
  QColor niceBlue(150, 150, 200);

  painter->setPen(thinPen);
  painter->setBrush(palette().foreground());
  painter->drawPolygon(QPolygon(3, &triangles[0][0]));

  QConicalGradient coneGradient(0, 0, -90);
  coneGradient.setColorAt(0.0, Qt::darkGray);
  coneGradient.setColorAt(0.2, niceBlue);
  coneGradient.setColorAt(0.5, Qt::white);
  coneGradient.setColorAt(1.0, Qt::darkGray);

  painter->setBrush(coneGradient);
  painter->drawEllipse(-46, -46, 92, 92);

  QRadialGradient haloGradient(0, 0, 20, 0, 0);
  haloGradient.setColorAt(0.0, Qt::lightGray);
  haloGradient.setColorAt(0.8, Qt::darkGray);
  haloGradient.setColorAt(0.9, Qt::white);
  haloGradient.setColorAt(1.0, Qt::black);

  painter->setPen(Qt::NoPen);
  painter->setBrush(haloGradient);
  painter->drawEllipse(-20, -20, 40, 40);

  QLinearGradient knobGradient(-7, -25, 7, -25);
  knobGradient.setColorAt(0.0, Qt::black);
  knobGradient.setColorAt(0.2, niceBlue);
  knobGradient.setColorAt(0.3, Qt::lightGray);
  knobGradient.setColorAt(0.8, Qt::white);
  knobGradient.setColorAt(1.0, Qt::black);

  painter->rotate(duration() * DegreesPerSecond);
  painter->setBrush(knobGradient);
  painter->setPen(thinPen);
  painter->drawRoundRect(-7, -25, 14 ,50, 150, 50);

#if 0
  for(int i=0; i<MaxMinutes; i++) {
    if (i%5 == 0) {
      painter->setPen(thickPen);
      painter->drawLine(0, -41, 0, -44);
      painter->drawText(-15, -41, 30, 25,
                        Qt::AlignHCenter | Qt::AlignTop,
                        QString::number(i));
    }
    else {
      painter->setPen(thinPen);
      painter->drawLine(0, -42, 0, -44);
    }

    painter->rotate(-DegreesPerMinute);
  }
#else
  for(int i=0; i<=MaxMinutes; i++) {
    painter->save();
    painter->rotate(-i * DegreesPerMinute);

    if (i%5 == 0) {
      painter->setPen(thickPen);
      painter->drawLine(0, -41, 0, -44);
      painter->drawText(-15, -41, 30, 25,
                        Qt::AlignHCenter | Qt::AlignTop,
                        QString::number(i));
    }
    else {
      painter->setPen(thinPen);
      painter->drawLine(0, -42, 0, -44);
    }
    painter->restore();
  }
#endif

}

void
OvenTimer::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);

  int side = qMin(width(), height());

  painter.setViewport((width()-side)/2, (height()-side)/2, side, side);

  painter.setWindow(-50, -50, 100, 100);
  draw(&painter);
}

void
OvenTimer::mousePressEvent(QMouseEvent *event)
{
  QPointF point = event->pos() - rect().center();
  double theta = atan2(-point.x(), -point.y()) * 180 / 3.1416;
  setDuration(duration() + int(theta / DegreesPerSecond));
  update();
}

