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
  setToolTip(QString::fromStdString(element->getName()));
  //  setZValue((m_position.x() + m_position.y()) % 2);

  setFlags(ItemIsSelectable | ItemIsMovable);
  setAcceptHoverEvents(true);
}

QRectF CircuitElementView::boundingRect() const {
    return QRectF(0, 0, 0, 0);
}

QPainterPath CircuitElementView::shape() const {
    QPainterPath path;
    path.addRect(0, 0, 0, 0);
    return path;
}

QPoint CircuitElementView::position() const {
  return m_position;
}

void CircuitElementView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*) {
  QColor fillColor = (option->state & QStyle::State_Selected) ? m_color.darker(150) : m_color;
  if(option->state & QStyle::State_MouseOver) {
    fillColor = fillColor.lighter(125);
  }
//  QColor fillColor = Qt::white;

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

  QPen pen = painter->pen();
  int width = 0;
  if(option->state & QStyle::State_Selected) {
    width += 1;
  }

  pen.setWidth(width);
  pen.setCapStyle(Qt::RoundCap);
  pen.setJoinStyle(Qt::RoundJoin);
  painter->setPen(pen);

  drawText(painter, lod);
  paintElement(painter, lod);
}

ModelDesign::Element& CircuitElementView::getElement() {
  return m_element;
}

const ModelDesign::Element& CircuitElementView::getElement() const {
  return m_element;
}


} // namespace Gui
} // namespace PowerLab
