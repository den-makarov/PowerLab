#ifndef GRAPHPROCESSOR_H
#define GRAPHPROCESSOR_H

#include <vector>

#include <QWidget>
#include <QBrush>
#include <QPen>

class QPainter;
class QPaintEvent;

namespace PowerLab {
namespace Gui {

class GraphProcessor {
public:
  struct GraphPoints {
    const std::vector<double>& x;
    const std::vector<double>& y;
  };

  GraphProcessor();

  void setPenColor(QColor color);
  void setPlotLimits(QRect plotLimits);

  void plot(QPainter *painter, GraphPoints points, QRectF graphValueLimits) const;

  void plot(QPainter *painter,
            const std::vector<double>& yData,
            const std::vector<double>& xData,
            double normYFactor = 1.0,
            double normXFactor = 1.0,
            double yBias = 0.0,
            double xBias = 0.0) const;

private:
  bool isPointInPlotLimits(const QPointF& point) const;

  QRect m_plotLimits;
  QPen m_pen;
};

} // namespace Gui
} // namespace PowerLab

#endif // GRAPHPROCESSOR_H
