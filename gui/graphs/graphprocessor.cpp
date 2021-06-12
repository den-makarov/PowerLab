#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QtMath>

#include "graphprocessor.h"
#include "plot.h"

namespace Gui {

GraphProcessor::GraphProcessor()
{
  background = QBrush(QColor(0xA4, 0xA4, 0xA4));
  penOne = QPen(Qt::black);
  penOne.setWidth(1);

  penTwo = QPen(Qt::blue);
  penTwo.setWidth(1);
}

struct ThreePhaseSignal {
  qreal a;
  qreal b;
  qreal c;
  qreal phA;
  qreal phB;
  qreal phC;
};

void GraphProcessor::paint(QPainter *painter, int elapsed) {
  if(painter == nullptr) {
    return;
  }

  painter->setPen(penOne);

  auto width = painter->window().width();
  auto height = painter->window().height();
  qreal factor = static_cast<qreal>(height / 2) * 0.8;

  ThreePhaseSignal signal;
  signal.phA = 2 * M_PI * elapsed / 5000;
  signal.phB = 2 * M_PI * elapsed / 5000 - 2 * M_PI / 3;
  signal.phC = 2 * M_PI * elapsed / 5000 + 2 * M_PI / 3;

  signal.a = factor * qSin(6 * M_PI * 0 / width + signal.phA);
  signal.b = factor * qSin(6 * M_PI * 0 / width + signal.phB);
  signal.c = factor * qSin(6 * M_PI * 0 / width + signal.phC);

  QPointF prePointA(0, signal.a + height / 2);
  QPointF prePointB(0, signal.b + height / 2);
  QPointF prePointC(0, signal.c + height / 2);

  for(int j = 1; j < width; j++) {
    signal.phA = 2 * M_PI * elapsed / 5000;
    signal.phB = 2 * M_PI * elapsed / 5000 - 2 * M_PI / 3;
    signal.phC = 2 * M_PI * elapsed / 5000 + 2 * M_PI / 3;

    signal.a = factor * qSin(6 * M_PI * j / width + signal.phA);
    signal.b = factor * qSin(6 * M_PI * j / width + signal.phB);
    signal.c = factor * qSin(6 * M_PI * j / width + signal.phC);

    QPointF pointA(j, signal.a + height / 2);
    QPointF pointB(j, signal.b + height / 2);
    QPointF pointC(j, signal.c + height / 2);

    penOne.setColor(Qt::red);
    painter->setPen(penOne);
    painter->drawLine(prePointA, pointA);
    prePointA = pointA;

    penOne.setColor(Qt::green);
    painter->setPen(penOne);
    painter->drawLine(prePointB, pointB);
    prePointB = pointB;

    penOne.setColor(Qt::blue);
    painter->setPen(penOne);
    painter->drawLine(prePointC, pointC);
    prePointC = pointC;
  }
}

void GraphProcessor::plot(QPainter *painter, QVector<double> x, double max) {
  painter->setPen(penOne);
  int scale = 400;
  int offset = 400;
  if(x.isEmpty()) {
    return;
  }

  if(max < 0.0) {
    scale = 100;
    offset = 100;
    painter->setPen(penTwo);
  }

  for(int j = 0; j < x.size(); j++) {
    qreal amp = offset - scale * x[j] / ((max + 0.0001) * 1.2);
    painter->drawPoint(QPointF(j, amp));
  }
}

Widget::Widget(GraphProcessor *graph, QWidget *parent)
  : QWidget(parent)
  , graph(graph)
{
  if(parent) {
    setFixedSize(parent->width() - 50, parent->height() - 50);
  } else {
    setFixedSize(400, 200);
  }
}

void Widget::setNames(QStringList names) {
  m_names = names;
}

void Widget::plot() {
  update();
}

void Widget::paintEvent(QPaintEvent *event)
{
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  Plot plot(event->rect().width(), event->rect().height(), true, 7, 3);
  plot.SetAxisLabel(Plot::Axis::X, "Time, [s]");
  if(!m_names.isEmpty()) {
    plot.SetAxisLabel(Plot::Axis::Y, m_names[0].toStdString());
  } else {
    plot.SetAxisLabel(Plot::Axis::Y, "Unknown");
  }
  plot.SetBounds({1.0, -1.0, 2.0, -2.0});
  plot.Update(&painter);

  graph->paint(&painter, 0);
  painter.end();
}

} // namespace Gui
