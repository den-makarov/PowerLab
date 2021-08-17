#include <QPainter>

#include "acvoltageview.h"

namespace PowerLab {
namespace Gui {

ACVoltageView::ACVoltageView(ModelDesign::Element element, QPoint position)
  : CircuitElementView(element, position)
{
}

void ACVoltageView::paintElement(QPainter* painter, qreal levelOfDetails) const {
  QVector<QLineF> lines;

  if(levelOfDetails >= 0.4) {
    // left -
    lines.push_back(QLineF(0, 35, 20, 35));
    // right -
    lines.push_back(QLineF(60, 35, 80, 35));
    painter->drawLines(lines);
    // outer circle
    painter->drawEllipse(QRectF(20, 15, 40, 40));
    // 2 arcs
    QRectF rect(40 - 4, 35, 8, 10);
    painter->drawArc(rect, -90 * 16, 180 * 16);

    rect.moveBottom(35);
    painter->drawArc(rect, 90 * 16, 180 * 16);
  }

  // Draw text
  if(levelOfDetails >= 2) {
    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    painter->scale(0.1, 0.1);
    painter->drawText(170, 180, QString("Model: at %1x%2")
                      .arg(position().x())
                      .arg(position().y()));
    painter->drawText(170, 200, QString("Serial number: SDSJ"));
    painter->drawText(170, 220, QString("Manufacturer: Chip Manufacturer"));
    painter->restore();
  }
}

} // namespace Gui
} // namespace PowerLab
