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
    lines.push_back(QLineF(0, 0, PIN_WIDTH, 0)); // left -
    lines.push_back(QLineF(20, -BODY_HEIGHT/2, 20, BODY_HEIGHT/2)); // left |
    lines.push_back(QLineF(70, -BODY_HEIGHT/2, 70, BODY_HEIGHT/2)); // right |
    lines.push_back(QLineF(20, BODY_HEIGHT/2, 70, BODY_HEIGHT/2)); // top -
    lines.push_back(QLineF(20, -BODY_HEIGHT/2, 70, -BODY_HEIGHT/2)); // bottom -
    lines.push_back(QLineF(70, 0, 70 + PIN_WIDTH, 0)); // right -
  }

  painter->drawLines(lines);
}

QRectF ResistorView::boundingRect() const {
  return QRectF(-1, -11, 92, 22);
}

QPainterPath ResistorView::shape() const {
  QPainterPath path;
  path.addRect(PIN_WIDTH, -BODY_HEIGHT/2, BODY_WIDTH, BODY_HEIGHT);
  return path;
}

void ResistorView::drawText(QPainter* painter, qreal levelOfDetails) const {
  if(levelOfDetails >= 2) {
    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    painter->scale(1, 1);
//    painter->drawText(170, 180, QString("Model: at %1x%2")
//                      .arg(position().x())
//                      .arg(position().y()));
//    painter->drawText(170, 200, QString("Serial number: SDSJ"));
//    painter->drawText(170, 220, QString("Manufacturer: Chip Manufacturer"));
    painter->restore();
  }
}

} // namespace Gui
} // namespace PowerLab
