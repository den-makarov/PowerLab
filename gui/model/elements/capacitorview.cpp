#include <QPainter>

#include "capacitorview.h"

namespace PowerLab {
namespace Gui {

CapacitorView::CapacitorView(ModelDesign::Element element, QPoint position)
  : CircuitElementView(element, position)
{
}

void CapacitorView::paintElement(QPainter* painter, qreal levelOfDetails) const {
  QVector<QLineF> lines;

  if(levelOfDetails >= 0.4) {
    lines.push_back(QLineF(0, 0, 20, 0)); // left -
    lines.push_back(QLineF(20, -15, 20, 15)); // left |
    lines.push_back(QLineF(25, -15, 25, 15)); // right |
    lines.push_back(QLineF(25, 0, 45, 0)); // right -
  }

  painter->drawLines(lines);
}

QRectF CapacitorView::boundingRect() const {
  return QRectF(-1, -16, 47, 32);
}

QPainterPath CapacitorView::shape() const {
  QPainterPath path;
  path.addRect(20, -15, 25, 30);
  return path;
}

void CapacitorView::drawText(QPainter*, qreal) const {
}

} // namespace Gui
} // namespace PowerLab
