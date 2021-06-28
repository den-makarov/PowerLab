#include <QPainter>

#include "graphprocessor.h"
#include "logger.h"

namespace PowerLab {
namespace Gui {

GraphProcessor::GraphProcessor() {
  m_background = QBrush(QColor(0xA4, 0xA4, 0xA4));
  m_pen = QPen(Qt::red);
  m_pen.setWidth(1);
}

void GraphProcessor::plot(QPainter *painter,
                          const std::vector<double>& yData,
                          const std::vector<double>& xData,
                          double normYFactor,
                          double normXFactor) const {
  if(yData.empty() || xData.empty() || xData.size() != yData.size()) {
    return;
  }

  painter->setPen(m_pen);
  double yFactor = (m_plotLimits.height() - 1) / normYFactor;
  double xFactor = (m_plotLimits.width() - 1) / normXFactor;

  int yOffset = (m_plotLimits.height() - 1) / 2 + m_plotLimits.top();
  int xOffset = m_plotLimits.left();

  QPointF point(xOffset + xFactor * xData[0], yOffset - yFactor * yData[0]);

  for(size_t i = 0; i < yData.size(); i++) {
    double y = yOffset - yFactor * yData[i];
    double x = xOffset + xFactor * xData[i];
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

void GraphProcessor::setPlotLimits(QRect plotLimits) {
  m_plotLimits = plotLimits;
}

} // namespace Gui
} // namespace PowerLab
