#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QtMath>

#include "graphprocessor.h"
#include "plot.h"

namespace {

struct ThreePhaseSignal {
  qreal a;
  qreal b;
  qreal c;
  qreal phA;
  qreal phB;
  qreal phC;
};

void paintDemoThreePhaseSignal(QPainter *painter, int bias = 0) {
  if(painter == nullptr) {
    return;
  }

  QPen pen(Qt::black);
  pen.setWidth(1);
  painter->setPen(pen);

  auto width = painter->window().width();
  auto height = painter->window().height();
  qreal factor = static_cast<qreal>(height / 2) * 0.8;

  ThreePhaseSignal signal;
  signal.phA = 2 * M_PI * bias / 5000;
  signal.phB = 2 * M_PI * bias / 5000 - 2 * M_PI / 3;
  signal.phC = 2 * M_PI * bias / 5000 + 2 * M_PI / 3;

  signal.a = factor * qSin(6 * M_PI * 0 / width + signal.phA);
  signal.b = factor * qSin(6 * M_PI * 0 / width + signal.phB);
  signal.c = factor * qSin(6 * M_PI * 0 / width + signal.phC);

  QPointF prePointA(0, signal.a + height / 2);
  QPointF prePointB(0, signal.b + height / 2);
  QPointF prePointC(0, signal.c + height / 2);

  for(int j = 1; j < width; j++) {
    signal.phA = 2 * M_PI * bias / 5000;
    signal.phB = 2 * M_PI * bias / 5000 - 2 * M_PI / 3;
    signal.phC = 2 * M_PI * bias / 5000 + 2 * M_PI / 3;

    signal.a = factor * qSin(6 * M_PI * j / width + signal.phA);
    signal.b = factor * qSin(6 * M_PI * j / width + signal.phB);
    signal.c = factor * qSin(6 * M_PI * j / width + signal.phC);

    QPointF pointA(j, signal.a + height / 2);
    QPointF pointB(j, signal.b + height / 2);
    QPointF pointC(j, signal.c + height / 2);

    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawLine(prePointA, pointA);
    prePointA = pointA;

    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawLine(prePointB, pointB);
    prePointB = pointB;

    pen.setColor(Qt::blue);
    painter->setPen(pen);
    painter->drawLine(prePointC, pointC);
    prePointC = pointC;
  }
}

} // namespace anonymous

namespace Gui {

GraphProcessor::GraphProcessor()
{
  m_background = QBrush(QColor(0xA4, 0xA4, 0xA4));
  m_penOne = QPen(Qt::black);
  m_penOne.setWidth(1);

  m_penTwo = QPen(Qt::blue);
  m_penTwo.setWidth(1);
}

void GraphProcessor::plot(QPainter *painter,
                          const std::vector<double>& x,
                          double normalizationFactor) const {
  painter->setPen(m_penOne);
  double plotVerticalFactor = painter->window().height() / 2.0;
  double plotHorizontalFactor = painter->window().width() / static_cast<double>(x.size());
  int offset = painter->window().height() / 2;
  if(x.empty()) {
    return;
  }

  QPointF point(0.0, offset - plotVerticalFactor * x[0] / normalizationFactor);

  for(size_t j = 0; j < x.size(); j++) {
    double amp = offset - plotVerticalFactor * x[j] / normalizationFactor;
    double delta = plotHorizontalFactor * static_cast<double>(j);
    QPointF nextPoint(delta, amp);
    painter->drawLine(point, nextPoint);
    point = nextPoint;
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

void GraphWidget::addGraphData(std::string name, std::vector<double> dataPoints) {
  if(m_graphs.find(name) == m_graphs.end()) {
    m_graphs.emplace(name, dataPoints);
  } else {
    // ERROR Attempt to add new graph with the similar name
  }
}

void GraphWidget::plot() {
  update();
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
  if(m_graphs.empty()) {
    // ERROR No graphs to plot
    return;
  }

  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  Plot plot(event->rect().width(), event->rect().height(), true, 7, 9);
  const auto& graphData = m_graphs.begin()->second;
  const auto& graphName = m_graphs.begin()->first;

  plot.setAxisLabel(Plot::Axis::X, "Time, [s]");
  plot.setAxisLabel(Plot::Axis::Y, graphName);

  auto maxValue = *std::max_element(graphData.begin(), graphData.end());
  auto minValue = *std::min_element(graphData.begin(), graphData.end());

  plot.setBounds({1.0, -1.0, maxValue, minValue});
  plot.update(&painter);

//  paintDemoThreePhaseSignal(&painter, 0);
  m_graphProcessor->plot(&painter, graphData, maxValue);
  painter.end();
}

} // namespace Gui
