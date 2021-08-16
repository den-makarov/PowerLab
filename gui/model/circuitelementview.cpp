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

void paintDiode(QPainter* painter, int xOffset) {
  QVector<QLineF> lines;
  int x = xOffset;
  // left -
  lines.push_back(QLineF(0 + x, 35, 20 + x, 35));
  // left |
  lines.push_back(QLineF(20 + x, 25, 20 + x, 45));
  // right |
  lines.push_back(QLineF(40 + x, 25, 40 + x, 45));
  // >
  lines.push_back(QLineF(20 + x, 25, 40 + x, 35));
  lines.push_back(QLineF(20 + x, 45, 40 + x, 35));
  // right -
  lines.push_back(QLineF(40 + x, 35, 60 + x, 35));
  painter->drawLines(lines);
}

void paintResistor(QPainter* painter, int xOffset) {
  QVector<QLineF> lines;
  int x = xOffset;
  // left -
  lines.push_back(QLineF(0 + x, 35, 20 + x, 35));
  // left |
  lines.push_back(QLineF(20 + x, 25, 20 + x, 45));
  // right |
  lines.push_back(QLineF(70 + x, 25, 70 + x, 45));
  // top -
  lines.push_back(QLineF(20 + x, 25, 70 + x, 25));
  // bottom -
  lines.push_back(QLineF(20 + x, 45, 70 + x, 45));
  // right -
  lines.push_back(QLineF(70 + x, 35, 90 + x, 35));

  painter->drawLines(lines);
}

void paintCapacitor(QPainter* painter, int xOffset) {
  QVector<QLineF> lines;
  int x = xOffset;
  // left -
  lines.push_back(QLineF(0 + x, 35, 20 + x, 35));
  // left |
  lines.push_back(QLineF(20 + x, 20, 20 + x, 50));
  // right |
  lines.push_back(QLineF(25 + x, 20, 25 + x, 50));
  // right -
  lines.push_back(QLineF(25 + x, 35, 45 + x, 35));

  painter->drawLines(lines);
}

void paintInductor(QPainter* painter, int xOffset) {
  QVector<QLineF> lines;
  int x = xOffset;
  // left -
  lines.push_back(QLineF(0 + x, 35, 20 + x, 35));
  // right -
  lines.push_back(QLineF(80 + x, 35, 100 + x, 35));
  painter->drawLines(lines);
  // 3 arcs
  for(int i = 0; i < 3; i++) {
    QRectF rect(i * 20 + (20 + x), 25, 20, 20);
    painter->drawArc(rect, 0, 180 * 16);
  }
}

void paintACVoltageSource(QPainter* painter, int xOffset) {
  QVector<QLineF> lines;
  int x = xOffset;
  // left -
  lines.push_back(QLineF(0 + x, 35, 20 + x, 35));
  // right -
  lines.push_back(QLineF(60 + x, 35, 80 + x, 35));
  painter->drawLines(lines);
  // outer circle
  painter->drawEllipse(QRectF(20 + x, 15, 40, 40));
  // 2 arcs
  QRectF rect(40 - 4 + x, 35, 8, 10);
  painter->drawArc(rect, -90 * 16, 180 * 16);
  rect.moveBottom(35);
  painter->drawArc(rect, 90 * 16, 180 * 16);
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

//    painter->drawRect(QRect(0, 0, 110, 70));
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
      paintDiode(painter, 0);
      paintResistor(painter, 60 + 10);
      paintCapacitor(painter, 60 + 10 + 90 + 10);
      paintInductor(painter, 60 + 10 + 90 + 10 + 45 + 10);
      paintACVoltageSource(painter, 60 + 10 + 90 + 10 + 45 + 10 + 100 + 10);
    }
    painter->drawLines(lines);
}

} // namespace Gui
} // namespace PowerLab
