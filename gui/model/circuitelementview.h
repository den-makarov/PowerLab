#ifndef CIRCUITELEMENTVIEW_H
#define CIRCUITELEMENTVIEW_H

#include <QColor>
#include <QPoint>
#include <QGraphicsItem>

#include "modeldesign/circuitelement.h"

namespace PowerLab {
namespace Gui {

class CircuitElementView : public QGraphicsItem {
public:
  explicit CircuitElementView(ModelDesign::Element element,
                              QPoint position);

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter,
             const QStyleOptionGraphicsItem *item,
             QWidget *widget) override;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
  ModelDesign::Element m_element;
  QPoint m_position;
  QColor m_color;
  QVector<QPointF> m_stuff;
};

} // namespace Gui
} // namespace PowerLab

#endif // CIRCUITELEMENTVIEW_H
