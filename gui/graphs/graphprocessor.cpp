#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QtMath>

#include "graphprocessor.h"
#include "plot.h"

namespace Gui {

GraphProcessor::GraphProcessor()
{
  m_background = QBrush(QColor(0xA4, 0xA4, 0xA4));
  m_penOne = QPen(Qt::black);
  m_penOne.setWidth(1);

  m_penTwo = QPen(Qt::blue);
  m_penTwo.setWidth(1);
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

  painter->setPen(m_penOne);

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

    m_penOne.setColor(Qt::red);
    painter->setPen(m_penOne);
    painter->drawLine(prePointA, pointA);
    prePointA = pointA;

    m_penOne.setColor(Qt::green);
    painter->setPen(m_penOne);
    painter->drawLine(prePointB, pointB);
    prePointB = pointB;

    m_penOne.setColor(Qt::blue);
    painter->setPen(m_penOne);
    painter->drawLine(prePointC, pointC);
    prePointC = pointC;
  }
}

void GraphProcessor::plot(QPainter *painter, QVector<double> x, double max) {
  painter->setPen(m_penOne);
  int scale = 400;
  int offset = 400;
  if(x.isEmpty()) {
    return;
  }

  if(max < 0.0) {
    scale = 100;
    offset = 100;
    painter->setPen(m_penTwo);
  }

  for(int j = 0; j < x.size(); j++) {
    qreal amp = offset - scale * x[j] / ((max + 0.0001) * 1.2);
    painter->drawPoint(QPointF(j, amp));
  }
}

GraphWidget::GraphWidget(GraphProcessor *graph, QWidget *parent)
  : QWidget(parent)
  , m_graphProcessor(graph)
{
  if(parent) {
    setFixedSize(parent->width() - 50, parent->height() - 50);
  } else {
    setFixedSize(400, 200);
  }
}

void GraphWidget::setNames(QStringList names) {
  m_names = names;
}

void GraphWidget::plot() {
  update();
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  Plot plot(event->rect().width(), event->rect().height(), true, 7, 3);
  plot.setAxisLabel(Plot::Axis::X, "Time, [s]");
  if(!m_names.isEmpty()) {
    plot.setAxisLabel(Plot::Axis::Y, m_names[0].toStdString());
  } else {
    plot.setAxisLabel(Plot::Axis::Y, "Unknown");
  }
  plot.setBounds({1.0, -1.0, 2.0, -2.0});
  plot.update(&painter);

  m_graphProcessor->paint(&painter, 0);
  painter.end();
}

} // namespace Gui
