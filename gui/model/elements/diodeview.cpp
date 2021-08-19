#include <QPainter>

#include "diodeview.h"

namespace PowerLab {
namespace Gui {

DiodeView::DiodeView(ModelDesign::Element element, QPoint position)
  : CircuitElementView(element, position)
{
}

void DiodeView::paintElement(QPainter* painter, qreal levelOfDetails) const {
  QVector<QLineF> lines;

  if(levelOfDetails >= 0.4) {
    lines.push_back(QLineF(0, 35, 20, 35)); // left -
    lines.push_back(QLineF(20, 25, 20, 45)); // left |
    lines.push_back(QLineF(40, 25, 40, 45)); // right |
    lines.push_back(QLineF(20, 25, 40, 35)); // >
    lines.push_back(QLineF(20, 45, 40, 35));
    lines.push_back(QLineF(40, 35, 60, 35)); // right -
  }

  painter->drawLines(lines);
}

QRectF DiodeView::boundingRect() const {
  return QRectF(-1, -1, 102, 12);
}

QPainterPath DiodeView::shape() const {
  QPainterPath path;
  path.addRect(20, 0, 80, 10);
  return path;
}

void DiodeView::drawText(QPainter*, qreal) const {
}

} // namespace Gui
} // namespace PowerLab
