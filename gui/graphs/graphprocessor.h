#ifndef GRAPHPROCESSOR_H
#define GRAPHPROCESSOR_H

#include <vector>

#include <QWidget>
#include <QBrush>
#include <QPen>

class QPainter;
class QPaintEvent;

namespace Gui {

class GraphProcessor {
public:
  GraphProcessor();

  void setPenColor(QColor color);
  void setPlotLimits(QRect plotLimits);
  void plot(QPainter *painter,
            const std::vector<double>& yData,
            const std::vector<double>& xData,
            double normalizationFactor = 1.0) const;

private:
  QRect m_plotLimits;
  QBrush m_background;
  QPen m_pen;
};

} // namespace Gui
#endif // GRAPHPROCESSOR_H
