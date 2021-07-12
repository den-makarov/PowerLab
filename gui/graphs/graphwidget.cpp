#include <algorithm>
#include <limits>
#include <cmath>

#include <QPainter>
#include <QPaintEvent>
#include <QtMath>
#include <QRubberBand>

#include "graphwidget.h"
#include "logger.h"

std::ostream& operator<<(std::ostream& out, QRectF rect) {
  out << "RectF: {" << rect.left()
      << ", " << rect.top()
      << ", " << rect.width()
      << ", " << rect.height()
      << "} Bottom right point {" << rect.right()
      << ", " << rect.bottom() << "}";
  return out;
}

namespace {

struct ThreePhaseSignal {
  qreal a;
  qreal b;
  qreal c;
  qreal alpha;
  qreal beta;
  qreal gamma;
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
  signal.alpha = 2 * M_PI * bias / 5000;
  signal.beta = 2 * M_PI * bias / 5000 - 2 * M_PI / 3;
  signal.gamma = 2 * M_PI * bias / 5000 + 2 * M_PI / 3;

  signal.a = factor * qSin(6 * M_PI * 0 / width + signal.alpha);
  signal.b = factor * qSin(6 * M_PI * 0 / width + signal.beta);
  signal.c = factor * qSin(6 * M_PI * 0 / width + signal.gamma);

  QPointF prePointA(0, signal.a + height / 2);
  QPointF prePointB(0, signal.b + height / 2);
  QPointF prePointC(0, signal.c + height / 2);

  for(int j = 1; j < width; j++) {
    signal.alpha = 2 * M_PI * bias / 5000;
    signal.beta = 2 * M_PI * bias / 5000 - 2 * M_PI / 3;
    signal.gamma = 2 * M_PI * bias / 5000 + 2 * M_PI / 3;

    signal.a = factor * qSin(6 * M_PI * j / width + signal.alpha);
    signal.b = factor * qSin(6 * M_PI * j / width + signal.beta);
    signal.c = factor * qSin(6 * M_PI * j / width + signal.gamma);

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

namespace PowerLab {
namespace Gui {

GraphWidget::~GraphWidget() {
  Logger::log(Logger::DefaultMessage::DEBUG_MSG, "Graph widget destructor");
}

GraphWidget::GraphWidget(QWidget *parent, GraphProcessor* graph, Plot* plot)
  : QWidget(parent)
  , m_graphProcessor(graph)
  , m_plot(plot)
{
  if(!m_graphProcessor) {
    m_graphProcessor = std::make_unique<GraphProcessor>();
  }

  if(!m_plot) {
    m_plot = std::make_unique<Plot>();
  }

  setFocusPolicy(Qt::StrongFocus);
}

QSize GraphWidget::sizeHint() const {
  return QSize(PREFERRED_WIDGIT_WIDTH_HINT, PREFERRED_WIDGIT_HEIGHT_HINT);
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
    m_graphs.back().color = defaultColorList[(m_graphs.size() - 1) % defaultColorList.size()];

    calcMinMaxGraphValues(m_graphs.back());
    resetGraphVerticalScale();
    updateVerticalLabels();
  } else {
    Logger::log(GuiMessage::ERROR_ATTEMPT_PLOT_SAME_SIGNAL, name);
  }
}

void GraphWidget::calcMinMaxGraphValues(GraphData& graph) {
  graph.minValue = *std::min_element(graph.points.begin(),
                                     graph.points.end());
  graph.maxValue = *std::max_element(graph.points.begin(),
                                     graph.points.end());
}

void GraphWidget::addHorizontalScaleData(std::string name,
                                         std::string units,
                                         std::vector<double>&& dataPoints) {
  m_horizontalScale = {name, units, std::move(dataPoints)};
  calcMinMaxGraphValues(m_horizontalScale);
  resetGraphHorizontalScale();
  updateHorizontalLabels();
}

void GraphWidget::updateHorizontalLabels() {
  m_plot->clearXAxisLabels();
  m_plot->addXAxisLabel(m_horizontalScale.name + " [" + m_horizontalScale.units + "]");
}

void GraphWidget::updateVerticalLabels() {
  m_plot->clearYAxisLabels();

  for(auto& graphData : m_graphs) {
    m_plot->addYAxisLabel(graphData.name + " [" + graphData.units + "]", graphData.color);
  }
}

void GraphWidget::updateHorizontalScale(double min, double max, double reserveAreaFactor) {
  auto plotBounds = m_plot->getBounds();

  if(std::fabs(max - min) < std::numeric_limits<double>::epsilon()) {
    plotBounds.xMax = max + reserveAreaFactor;
    plotBounds.xMin = min - reserveAreaFactor;
  } else {
    plotBounds.xMin = min - (max - min) * reserveAreaFactor;
    plotBounds.xMax = max + (max - min) * reserveAreaFactor;
  }

  m_plot->setBounds(plotBounds);
}

void GraphWidget::estimateVerticalMinMaxValue(double& min, double& max) const {
  for(auto& graphData : m_graphs) {
    if(min > graphData.minValue) {
      min = graphData.minValue;
    }

    if(max < graphData.maxValue) {
      max = graphData.maxValue;
    }
  }
}

void GraphWidget::updateVerticalScale(double min, double max, double reserveAreaFactor) {
  auto plotBounds = m_plot->getBounds();

  if(std::fabs(max - min) < std::numeric_limits<double>::epsilon()) {
    plotBounds.yMax = max + max * reserveAreaFactor;
    plotBounds.yMin = max - max * reserveAreaFactor;
  } else {
    plotBounds.yMin = min - (max - min) * reserveAreaFactor;
    plotBounds.yMax = max + (max - min) * reserveAreaFactor;
  }

  m_plot->setBounds(plotBounds);
}

void GraphWidget::setupDefaultPlotMargins() const {
  auto margins = m_plot->getMargins();

  margins.left = 60;
  margins.right = 20;
  margins.top = 20;
  margins.bottom = 25;

  m_plot->setMargins(margins);
}

void GraphWidget::paintEvent(QPaintEvent *event) {
  if(m_graphs.size() < 1) {
    Logger::log(GuiMessage::ERROR_NO_DATA_TO_PLOT);
    return;
  }

  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  if(event) {
    m_plot->setArea(event->rect().width(), event->rect().height());
  } else {
    m_plot->setArea(width(), height());
  }

  m_plot->setBackground(QColor(0xFF, 0xFF, 0xA0));
  setupDefaultPlotMargins();
  m_graphProcessor->setPlotLimits(m_plot->getMarginsRect());

  m_plot->update(&painter);

//  paintDemoThreePhaseSignal(&painter, 0);
  for(auto& graphData : m_graphs) {
    m_graphProcessor->setPenColor(graphData.color);
    GraphProcessor::GraphPoints points{m_horizontalScale.points, graphData.points};
    m_graphProcessor->plot(&painter, points, m_plot->getBoundsRect());
  }
  painter.end();
}

void GraphWidget::mousePressEvent(QMouseEvent *event) {
  if(m_zoomEnabled && event->button() == Qt::LeftButton) {
    zoomBegin(event->globalPos(), event->pos());
  }
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event) {
  if(m_zoomEnabled) {
    zoomUpdate(event->globalPos(), event->pos());
  }
}

void GraphWidget::mouseReleaseEvent(QMouseEvent*) {
  if(m_zoomEnabled) {
    zoomFinish();
  }
}

bool GraphWidget::checkIfPointInGraphLimits(QPoint point) const {
  auto plotArea = m_plot->getMarginsRect();
  if(point.x() < plotArea.left() || plotArea.right() < point.x()) {
    return false;
  }

  if(point.y() < plotArea.top() || plotArea.bottom() < point.y()) {
    return false;
  }

  return true;
}

QRectF GraphWidget::zoomValueBoundsByFactor(double factor) const {
  auto zoomBounds = m_plot->getMarginsRect();
  double heightHalf = zoomBounds.height() / 2.0;
  double heightMiddle = heightHalf + zoomBounds.top();

  zoomBounds.setTop(static_cast<int>(heightMiddle - heightHalf / factor));
  zoomBounds.setBottom(static_cast<int>(heightMiddle + heightHalf / factor));

  return calcValuesBoundFromZoomArea(zoomBounds);
}

QRectF GraphWidget::calcValuesBoundFromZoomArea(QRect zoomArea) const {
  QRectF zoomBounds = m_plot->getBoundsRect();
  QRect margins = m_plot->getMarginsRect();
  zoomArea.translate(-margins.left(), -margins.top());

  zoomBounds.translate(zoomArea.left() * zoomBounds.width() / margins.width(),
                       -zoomArea.top() * zoomBounds.height() / margins.height());

  zoomBounds.setWidth(zoomArea.width() * zoomBounds.width() / margins.width());

  // Top and bottom points should be mirrored
  auto top = zoomBounds.bottom();
  zoomBounds.setHeight( - zoomArea.height() * zoomBounds.height() / margins.height());
  zoomBounds.moveTop(top);

  return zoomBounds;
}

void GraphWidget::resetGraphVerticalScale() {
  double min = std::numeric_limits<double>::max();
  double max = std::numeric_limits<double>::min();
  estimateVerticalMinMaxValue(min, max);
  updateVerticalScale(min, max, PLOT_VERTICAL_EXTENSION);
}

void GraphWidget::resetGraphHorizontalScale() {
  double min = m_horizontalScale.minValue;
  double max = m_horizontalScale.maxValue;
  updateHorizontalScale(min, max, PLOT_HORIZONTAL_EXTENSION);
}

void GraphWidget::resetDefaultView() {
  resetGraphVerticalScale();
  resetGraphHorizontalScale();
  this->repaint();
}

void GraphWidget::zoomFinish() {
  if(m_zoomArea && m_zoomArea->isActive()) {
    m_zoomArea->hide();

    auto area = m_zoomArea->getLocalArea();
    QRectF zoomBounds;

    if(area.width() < 3 && area.height() < 3) {
      zoomBounds = zoomValueBoundsByFactor(ZOOM_DEFAULT_FACTOR);
    } else {
      zoomBounds = calcValuesBoundFromZoomArea(area);
    }

    std::ostringstream msg;
    msg << "Zoomed area: " << zoomBounds;
    Logger::log(Logger::DefaultMessage::DEBUG_MSG, msg.str());

    updateVerticalScale(zoomBounds.bottom(), zoomBounds.top(), 0.0);
    updateHorizontalScale(zoomBounds.left(), zoomBounds.right(), 0.0);
    this->repaint();
  }
}

void GraphWidget::zoomUpdate(QPoint global, QPoint local) {
  if(m_zoomArea && checkIfPointInGraphLimits(local)) {
    m_zoomArea->updateArea(global);
  }
}

void GraphWidget::zoomBegin(QPoint global, QPoint local) {
  if(checkIfPointInGraphLimits(local)) {
    if(!m_zoomArea) {
      m_zoomArea = std::make_unique<ZoomSelectionRectArea>();
    }
    m_zoomArea->setAreaOrigin(global, local);
    m_zoomArea->show();
  }
}

void GraphWidget::setZoomEnabled(bool enabled) {
  m_zoomEnabled = enabled;
}

} // namespace Gui
} // namespace PowerLab
