#include <QPainter>

#include "resistorview.h"

namespace PowerLab {
namespace Gui {

ResistorView::ResistorView(ModelDesign::Element element, QPoint position)
  : CircuitElementView(element, position)
{
}

void ResistorView::paintElement(QPainter* painter, qreal levelOfDetails) const {
  QVector<QLineF> lines;

  if(levelOfDetails >= 0.4) {
    // left -
    lines.push_back(QLineF(0, 35, 20, 35));
    // left |
    lines.push_back(QLineF(20, 25, 20, 45));
    // right |
    lines.push_back(QLineF(70, 25, 70, 45));
    // top -
    lines.push_back(QLineF(20, 25, 70, 25));
    // bottom -
    lines.push_back(QLineF(20, 45, 70, 45));
    // right -
    lines.push_back(QLineF(70, 35, 90, 35));

    painter->drawLines(lines);
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
