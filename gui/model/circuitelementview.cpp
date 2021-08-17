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

QPoint CircuitElementView::position() const {
  return m_position;
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
  if(option->state & QStyle::State_Selected) {
    width += 2;
  }

  pen.setWidth(width);
  paintElement(painter, lod);
}

} // namespace Gui
} // namespace PowerLab
