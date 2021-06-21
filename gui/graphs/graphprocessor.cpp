#include <QPainter>

#include "graphprocessor.h"
#include "logger.h"

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

} // namespace Gui
