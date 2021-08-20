#include <QPainter>

#include "inductorview.h"

namespace PowerLab {
namespace Gui {

InductorView::InductorView(ModelDesign::Element element)
  : CircuitElementView(element)
{
}

void InductorView::paintElement(QPainter* painter, qreal levelOfDetails) const {
  if(levelOfDetails >= 0.4) {
    QVector<QLineF> lines;

    lines.push_back(QLineF(0, 0, 20, 0)); // left -
    lines.push_back(QLineF(80, 0, 100, 0)); // right -
    painter->drawLines(lines);

    for(int i = 0; i < 3; i++) { // 3 arcs
      QRectF rect(i * 20 + 20, -10, 20, 20);
      painter->drawArc(rect, 0, 180 * 16);
    }
  }
}

QRectF InductorView::boundingRect() const {
  return QRectF(-1, -11, 102, 22);
}

QPainterPath InductorView::shape() const {
  QPainterPath path;
  path.addRect(20, 0, 60, -10);
  return path;
}

void InductorView::drawText(QPainter*, qreal) const {
}

} // namespace Gui
} // namespace PowerLab
