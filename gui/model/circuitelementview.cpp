#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "circuitelementview.h"

namespace PowerLab {
namespace Gui {

CircuitElementView::CircuitElementView(ModelDesign::Element element,
                                       QPoint position)
  : m_element(element)
  , m_position(position)
{
  setZValue((m_position.x() + m_position.y()) % 2);

  setFlags(ItemIsSelectable | ItemIsMovable);
  setAcceptHoverEvents(true);
}

QRectF CircuitElementView::boundingRect() const {
    return QRectF(0, 0, 110, 70);
}

QPainterPath CircuitElementView::shape() const {
    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    return path;
}

void paintDiode(QVector<QLineF>& lines, int xOffset) {
  int x = xOffset;
  // left -
  lines.push_back(QLineF(0 + x, 35, 35 + x, 35));
  // left |
  lines.push_back(QLineF(35 + x, 0, 35 + x, 70));
  // right |
  lines.push_back(QLineF(80 + x, 00, 80 + x, 70));
  // >
  lines.push_back(QLineF(35 + x, 0, 80 + x, 35));
  lines.push_back(QLineF(35 + x, 70, 80 + x, 35));
  // right -
  lines.push_back(QLineF(80 + x, 35, 110 + x, 35));
}

void paintResistor(QVector<QLineF>& lines, int xOffset) {
  int x = xOffset;
  // left -
  lines.push_back(QLineF(5 + x, 35, 25 + x, 35));
  // left |
  lines.push_back(QLineF(25 + x, 20, 25 + x, 50));
  // right |
  lines.push_back(QLineF(90 + x, 20, 90 + x, 50));
  // top -
  lines.push_back(QLineF(25 + x, 20, 90 + x, 20));
  // bottom -
  lines.push_back(QLineF(25 + x, 50, 90 + x, 50));
  // right -
  lines.push_back(QLineF(90 + x, 35, 110 + x, 35));
}

void paintCapacitor(QVector<QLineF>& lines, int xOffset) {
  int x = xOffset;
  // left -
  lines.push_back(QLineF(5 + x, 35, 25 + x, 35));
  // left |
  lines.push_back(QLineF(25 + x, 20, 25 + x, 50));
  // right |
  lines.push_back(QLineF(30 + x, 20, 30 + x, 50));
  // right -
  lines.push_back(QLineF(30 + x, 35, 50 + x, 35));
}

void paintInductor(QVector<QLineF>& lines, int xOffset) {
  int x = xOffset;
  // left -
  lines.push_back(QLineF(5 + x, 35, 25 + x, 35));
  // 3 arcs
  // right -
  lines.push_back(QLineF(90 + x, 35, 110 + x, 35));
}

void paintACVoltageSource(QVector<QLineF>& lines, int xOffset) {
  int x = xOffset;
  lines.push_back(QLineF(0 + x, 0, 0, 0));
}

void CircuitElementView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*) {
//    QColor fillColor = (option->state & QStyle::State_Selected) ? m_color.darker(150) : m_color;
//    if (option->state & QStyle::State_MouseOver)
//        fillColor = fillColor.lighter(125);
    QColor fillColor = Qt::white;

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    if (lod < 0.2) {
        if (lod < 0.125) {
            painter->fillRect(QRectF(0, 0, 110, 70), fillColor);
            return;
        }

        QBrush b = painter->brush();
        painter->setBrush(fillColor);
        painter->drawRect(13, 13, 97, 57);
        painter->setBrush(b);
        return;
    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.darker(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(0, 0, 110, 70));
    painter->setBrush(b);

    // Draw text
    if (lod >= 2) {
        QFont font("Times", 10);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setFont(font);
        painter->save();
        painter->scale(0.1, 0.1);
        painter->drawText(170, 180, QString("Model: at %1x%2")
                          .arg(m_position.x())
                          .arg(m_position.y()));
        painter->drawText(170, 200, QString("Serial number: SDSJ"));
        painter->drawText(170, 220, QString("Manufacturer: Chip Manufacturer"));
        painter->restore();
    }

    // Draw lines
    QVector<QLineF> lines;
// Diode
    if (lod >= 0.4) {
      paintDiode(lines, 0);
      paintResistor(lines, 120);
      paintCapacitor(lines, 240);
      paintInductor(lines, 360);
//      paintACVoltageSource(lines, 480);
    }
    painter->drawLines(lines);
}

} // namespace Gui
} // namespace PowerLab
