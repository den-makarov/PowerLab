#include <QPainter>

#include "acvoltageview.h"

namespace PowerLab {
namespace Gui {

ACVoltageView::ACVoltageView(ModelDesign::Element element, QPoint position)
  : CircuitElementView(element, position)
{
}

void ACVoltageView::paintElement(QPainter* painter, qreal levelOfDetails) const {
  if(levelOfDetails >= 0.4) {
    QVector<QLineF> lines;

    lines.push_back(QLineF(0, 35, 20, 35)); // left -
    lines.push_back(QLineF(60, 35, 80, 35)); // right -
    painter->drawLines(lines);

    painter->drawEllipse(QRectF(20, 15, 40, 40)); // outer circle
    QRectF rect(40 - 4, 35, 8, 10); // first half of sin
    painter->drawArc(rect, -90 * 16, 180 * 16);

    rect.moveBottom(35); // first half of sin
    painter->drawArc(rect, 90 * 16, 180 * 16);
  }
}

QRectF ACVoltageView::boundingRect() const {
  return QRectF(-1, -11, 92, 22);
}

QPainterPath ACVoltageView::shape() const {
  QPainterPath path;
  path.addRect(20, -10, 50, 20);
  return path;
}

void ACVoltageView::drawText(QPainter*, qreal) const {
}

} // namespace Gui
} // namespace PowerLab
