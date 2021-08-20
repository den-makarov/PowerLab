#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "circuitelementview.h"

namespace PowerLab {
namespace Gui {

CircuitElementView::CircuitElementView(ModelDesign::Element element)
  : m_element(element)
{
  setToolTip(QString::fromStdString(element->getName()));
  setFlags(ItemIsSelectable | ItemIsMovable);
  setAcceptHoverEvents(true);
}

void CircuitElementView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*) {
  QPen pen = painter->pen();
  auto oldPen = pen;

  pen.setWidth(1);
  pen.setColor(Qt::black);
  if(option->state & QStyle::State_Selected) {
    pen.setWidth(2);
  } else if(option->state & QStyle::State_MouseOver) {
    pen.setColor(Qt::darkBlue);
  }

  pen.setCapStyle(Qt::RoundCap);
  pen.setJoinStyle(Qt::RoundJoin);
  painter->setPen(pen);

  const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
  drawText(painter, lod);
  paintElement(painter, lod);
  painter->setPen(oldPen);
}

ModelDesign::Element& CircuitElementView::getElement() {
  return m_element;
}

const ModelDesign::Element& CircuitElementView::getElement() const {
  return m_element;
}


} // namespace Gui
} // namespace PowerLab
