#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QtMath>

#include "graphprocessor.h"
#include "logger.h"
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

static std::vector<QColor> defaultColorList = {
  Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow, Qt::gray
};

} // namespace anonymous

namespace Gui {

GraphProcessor::GraphProcessor() {
  m_background = QBrush(QColor(0xA4, 0xA4, 0xA4));
  m_pen = QPen(Qt::red);
  m_pen.setWidth(1);
}

void GraphProcessor::plot(QPainter *painter,
                          const std::vector<double>& yData,
                          const std::vector<double>& xData,
                          double normalizationFactor) const {
  if(yData.empty() || xData.empty() || xData.size() != yData.size()) {
    return;
  }

  painter->setPen(m_pen);

  double plotVerticalFactor = painter->window().height() / 2.0;
  double plotHorizontalFactor = painter->window().width() / (1.0 * xData.back());
  int offset = painter->window().height() / 2;

  QPointF point(0.0, offset - plotVerticalFactor * yData[0] / normalizationFactor);

  for(size_t j = 0; j < yData.size(); j++) {
    double y = offset - plotVerticalFactor * yData[j] / normalizationFactor;
    double x = plotHorizontalFactor * xData[j];
    QPointF nextPoint(x, y);
    if(nextPoint != point) {
      painter->drawLine(point, nextPoint);
      point = nextPoint;
    }
  }
}

void GraphProcessor::setPenColor(QColor color) {
  m_pen.setColor(color);
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

void GraphWidget::plot() {
  update();
}

void GraphWidget::addGraphData(std::string name,
                               std::string units,
                               std::vector<double> dataPoints) {
  if(m_graphs.find(name) == m_graphs.end()) {
    m_graphs.emplace(name, GraphData{units, dataPoints, 0.0, 0.0});
  } else {
    Logger::log(GuiMessage::ERROR_ATTEMPT_PLOT_SAME_SIGNAL, name);
  }
}

void GraphWidget::addHorizontalScaleData(std::string name,
                                         std::string units,
                                         std::vector<double> dataPoints) {
  m_horizontalScale.first = name;
  m_horizontalScale.second.units = units;
  m_horizontalScale.second.points = dataPoints;
}

void GraphWidget::configureHorizontalScale(Plot& plot) {
  auto& graphData = m_horizontalScale.second;
  auto& graphName = m_horizontalScale.first;

  graphData.minValue = graphData.points.front();
  graphData.maxValue = graphData.points.back();

  plot.setAxisLabel(Plot::Axis::X, graphName + ", [" + graphData.units + "]");
  auto& plotBounds = plot.getBounds();
  plotBounds.xMin = graphData.minValue;
  plotBounds.xMax = graphData.maxValue;
}

void GraphWidget::configureVerticalScale(Plot& plot) {
  for(auto& [graphName, graphData] : m_graphs) {
    plot.setAxisLabel(Plot::Axis::Y, graphName + ", [" + graphData.units + "]");
    auto& plotBounds = plot.getBounds();

    graphData.minValue = *std::min_element(graphData.points.begin(),
                                           graphData.points.end());
    graphData.maxValue = *std::max_element(graphData.points.begin(),
                                           graphData.points.end());

    plotBounds.yMin = graphData.minValue;
    plotBounds.yMax = graphData.maxValue;
  }
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
  if(m_graphs.size() < 1) {
    Logger::log(GuiMessage::ERROR_NO_DATA_TO_PLOT);
    return;
  }

  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  Plot plot(event->rect().width(), event->rect().height(), true, 7, 9);
  configureHorizontalScale(plot);
  configureVerticalScale(plot);

  plot.update(&painter);

//  paintDemoThreePhaseSignal(&painter, 0);
  size_t penColorId = 0;
  for(auto& [graphName, graphData] : m_graphs) {
    m_graphProcessor->setPenColor(defaultColorList[penColorId++]);
    penColorId %= defaultColorList.size();

    m_graphProcessor->plot(&painter,
                           graphData.points,
                           m_horizontalScale.second.points,
                           graphData.maxValue);
  }
  painter.end();
}

} // namespace Gui
