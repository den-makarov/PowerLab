#include <QPainter>

#include "diodeview.h"

namespace PowerLab {
namespace Gui {

DiodeView::DiodeView(ModelDesign::Element element)
  : CircuitElementView(element)
{
}

void DiodeView::paintElement(QPainter* painter, qreal levelOfDetails) const {
  QVector<QLineF> lines;

  if(levelOfDetails >= 0.4) {
    lines.push_back(QLineF(0, 0, 20, 0)); // left -
    lines.push_back(QLineF(20, -10, 20, 10)); // left |
    lines.push_back(QLineF(40, -10, 40, 10)); // right |
    lines.push_back(QLineF(20, -10, 40, 0)); // >
    lines.push_back(QLineF(20, 10, 40, 0));
    lines.push_back(QLineF(40, 0, 60, 0)); // right -
  }

  painter->drawLines(lines);
}

QRectF DiodeView::boundingRect() const {
  return QRectF(-1, -11, 62, 22);
}

QPainterPath DiodeView::shape() const {
  QPainterPath path;
  path.addRect(20, -10, 20, 20);
  return path;
}

void DiodeView::drawText(QPainter*, qreal) const {
}

} // namespace Gui
} // namespace PowerLab
