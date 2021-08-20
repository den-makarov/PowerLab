#include <QPainter>

#include "acvoltageview.h"

namespace PowerLab {
namespace Gui {

ACVoltageView::ACVoltageView(ModelDesign::Element element)
  : CircuitElementView(element)
{
}

void ACVoltageView::paintElement(QPainter* painter, qreal levelOfDetails) const {
  if(levelOfDetails >= 0.4) {
    QVector<QLineF> lines;

    lines.push_back(QLineF(0, 0, 20, 0)); // left -
    lines.push_back(QLineF(60, 0, 80, 0)); // right -
    painter->drawLines(lines);

    painter->drawEllipse(QRectF(20, -20, 40, 40)); // outer circle
    QRectF rect(40 - 4, 0, 8, 10); // first half of sin
    painter->drawArc(rect, -90 * 16, 180 * 16);

    rect.moveBottom(0); // first half of sin
    painter->drawArc(rect, 90 * 16, 180 * 16);
  }
}

QRectF ACVoltageView::boundingRect() const {
  return QRectF(-1, -21, 82, 42);
}

QPainterPath ACVoltageView::shape() const {
  QPainterPath path;
  path.addEllipse(20, -20, 40, 40);
  return path;
}

void ACVoltageView::drawText(QPainter*, qreal) const {
}

} // namespace Gui
} // namespace PowerLab
