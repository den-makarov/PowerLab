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
    QVarLengthArray<QLineF, 6> lines;
//    if (lod >= 0.5) {
//        lines.append(QLineF(5, 35, 13, 35));
//        lines.append(QLineF(94, 35, 102, 35));
//    }

// Diode
    if (lod >= 0.4) {
        const QLineF lineData[] = {
          // left -
          QLineF(0, 35, 35, 35),

          // left |
          QLineF(35, 0, 35, 70),
          // right |
          QLineF(80, 00, 80, 70),

          // >
          QLineF(35, 0, 80, 35),
          QLineF(35, 70, 80, 35),

          // right -
          QLineF(80, 35, 110, 35)
        };
        lines.append(lineData, 6);
    }
    painter->drawLines(lines.data(), lines.size());
}

} // namespace Gui
} // namespace PowerLab
