#include <algorithm>
#include <limits>
#include <cmath>

#include <QPainter>
#include <QPaintEvent>
#include <QtMath>

#include "graphwidget.h"
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

GraphWidget::~GraphWidget() {
  Logger::log(Logger::DefaultMessage::DEBUG_MSG, "Graph widget destructor");
}

GraphWidget::GraphWidget(QWidget *parent, GraphProcessor* graph)
  : QWidget(parent)
  , m_graphProcessor(graph)
{
  if(parent) {
    auto geometry = parent->geometry();
    geometry.adjust(0, 0, -10, -10);
    setGeometry(geometry);
  }

  if(!m_graphProcessor) {
    m_graphProcessor = std::make_unique<GraphProcessor>();
  }
}

void GraphWidget::plot() {
  update();
}

void GraphWidget::addGraphData(std::string name,
                               std::string units,
                               std::vector<double>&& dataPoints) {
  auto contains = std::any_of(m_graphs.begin(), m_graphs.end(), [&name](const GraphData& data){
    return data.name == name;
  });

  if(!contains) {
    m_graphs.push_back({name, units, std::move(dataPoints), 0.0, 0.0});
  } else {
    Logger::log(GuiMessage::ERROR_ATTEMPT_PLOT_SAME_SIGNAL, name);
  }
}

void GraphWidget::addHorizontalScaleData(std::string name,
                                         std::string units,
                                         std::vector<double>&& dataPoints) {
  m_horizontalScale = {name, units, std::move(dataPoints)};
}

void GraphWidget::configureHorizontalScale(Plot& plot) {
  auto& g = m_horizontalScale;

  plot.addXAxisLabel(g.name + " [" + g.units + "]");

  g.minValue = *std::min_element(g.points.begin(), g.points.end());

  g.maxValue = *std::max_element(g.points.begin(), g.points.end());

  auto& plotBounds = plot.getBounds();
  if(std::fabs(g.maxValue - g.minValue) < std::numeric_limits<double>::epsilon()) {
    plotBounds.xMax = g.maxValue + PLOT_HORIZONTAL_EXTENSION;
    plotBounds.xMin = g.maxValue - PLOT_HORIZONTAL_EXTENSION;
  } else {
    plotBounds.xMin = g.minValue * PLOT_HORIZONTAL_EXTENSION;
    plotBounds.xMax = g.maxValue * PLOT_HORIZONTAL_EXTENSION;
  }
}

void GraphWidget::configureVerticalScale(Plot& plot) {
  double min = std::numeric_limits<double>::max();
  double max = std::numeric_limits<double>::min();

  for(auto& graphData : m_graphs) {
    plot.addYAxisLabel(graphData.name + " [" + graphData.units + "]");

    graphData.minValue = *std::min_element(graphData.points.begin(),
                                           graphData.points.end());
    if(min > graphData.minValue) {
      min = graphData.minValue;
    }

    graphData.maxValue = *std::max_element(graphData.points.begin(),
                                           graphData.points.end());
    if(max < graphData.maxValue) {
      max = graphData.maxValue;
    }
  }

  auto& plotBounds = plot.getBounds();
  if(std::fabs(max - min) < std::numeric_limits<double>::epsilon()) {
    plotBounds.yMax = max + PLOT_VERTICAL_EXTENSION;
    plotBounds.yMin = max - PLOT_VERTICAL_EXTENSION;
  } else {
    plotBounds.yMin = min * PLOT_VERTICAL_EXTENSION;
    plotBounds.yMax = max * PLOT_VERTICAL_EXTENSION;
  }
}

void GraphWidget::paintEvent(QPaintEvent *event) {
  if(m_graphs.size() < 1) {
    Logger::log(GuiMessage::ERROR_NO_DATA_TO_PLOT);
    return;
  }

  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  Plot plot(event->rect().width(), event->rect().height());
  plot.setBackground(QColor(0xFF, 0xFF, 0xA0));
  plot.setBorder(true);
  plot.setMainGridLinesNumber(7, 11);
  auto& margins = plot.getMargins();
  margins.left = 40;
  margins.right = 20;
  margins.top = 20;
  margins.bottom = 20;

  m_graphProcessor->setPlotLimits(QRect(margins.left,
                                        margins.top,
                                        plot.getWidth() - (margins.right + margins.left),
                                        plot.getHeight() - (margins.bottom + margins.top)));

  configureHorizontalScale(plot);
  configureVerticalScale(plot);

  plot.update(&painter);

//  paintDemoThreePhaseSignal(&painter, 0);
  size_t penColorId = 0;
  for(auto& graphData : m_graphs) {
    m_graphProcessor->setPenColor(defaultColorList[penColorId++]);
    penColorId %= defaultColorList.size();

    m_graphProcessor->plot(&painter,
                           graphData.points,
                           m_horizontalScale.points,
                           plot.getBounds().yMax - plot.getBounds().yMin,
                           plot.getBounds().xMax - plot.getBounds().xMin);
  }
  painter.end();
}

} // namespace Gui