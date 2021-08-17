#include <QPainter>

#include "inductorview.h"

namespace PowerLab {
namespace Gui {

InductorView::InductorView(ModelDesign::Element element, QPoint position)
  : CircuitElementView(element, position)
{
}

void InductorView::paintElement(QPainter* painter, qreal levelOfDetails) const {
  QVector<QLineF> lines;

  if(levelOfDetails >= 0.4) {
    // left -
    lines.push_back(QLineF(0, 35, 20, 35));
    // right -
    lines.push_back(QLineF(80, 35, 100, 35));
    painter->drawLines(lines);
    // 3 arcs
    for(int i = 0; i < 3; i++) {
      QRectF rect(i * 20 + 20, 25, 20, 20);
      painter->drawArc(rect, 0, 180 * 16);
    }
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
