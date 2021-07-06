#include <QPainter>

#include "graphprocessor.h"
#include "logger.h"

namespace PowerLab {
namespace Gui {

GraphProcessor::GraphProcessor()
  : m_pen(Qt::red)
{
  m_pen.setWidth(1);
}

void GraphProcessor::plot(QPainter *painter, GraphPoints points, QRectF graphValueLimits) const {
  if(!painter) {
    return;
  }

  plot(painter,
       points.y,
       points.x,
       graphValueLimits.height(),
       graphValueLimits.width(),
       (graphValueLimits.top() + graphValueLimits.bottom()) / 2.0,
       (graphValueLimits.left() + graphValueLimits.right()) / 2.0);

}

void GraphProcessor::plot(QPainter *painter,
                          const std::vector<double>& yData,
                          const std::vector<double>& xData,
                          double normYFactor,
                          double normXFactor,
                          double yBias,
                          double xBias) const {
  if(!painter || yData.empty() || xData.empty() || xData.size() != yData.size()) {
    return;
  }

  painter->setPen(m_pen);

  double yOffset = (m_plotLimits.height() - 1) / 2 + m_plotLimits.top();
  double xOffset = (m_plotLimits.width() - 1) / 2 + m_plotLimits.left();
  double yFactor = (m_plotLimits.height() - 1) / normYFactor;
  double xFactor = (m_plotLimits.width() - 1) / normXFactor;

  QPointF point(xOffset + xFactor * (xData[0] - xBias), yOffset - yFactor * (yData[0] - yBias));

  for(size_t i = 0; i < yData.size(); i++) {
    double y = yOffset - yFactor * (yData[i] - yBias);
    double x = xOffset + xFactor * (xData[i] - xBias);
    QPointF nextPoint(x, y);

    if(!isPointInPlotLimits(nextPoint) || !isPointInPlotLimits(point)) {
      point = nextPoint;
    } else if(nextPoint != point) {
      painter->drawLine(point, nextPoint);
      point = nextPoint;
    }
  }
}

bool GraphProcessor::isPointInPlotLimits(const QPointF& point) const {
  // Right bound is strict in order to eliminate graphical glitch
  if(point.x() <= m_plotLimits.left() || m_plotLimits.right() < point.x()) {
    return false;
  }

  if(point.y() <= m_plotLimits.top() || m_plotLimits.bottom() <= point.y()) {
    return false;
  }

  return true;
}

void GraphProcessor::setPenColor(QColor color) {
  m_pen.setColor(color);
}

void GraphProcessor::setPlotLimits(QRect plotLimits) {
  m_plotLimits = plotLimits;
}

} // namespace Gui
} // namespace PowerLab
