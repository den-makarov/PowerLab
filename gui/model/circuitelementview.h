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

private:
  ModelDesign::Element m_element;
  QPoint m_position;
  QColor m_color;
};

} // namespace Gui
} // namespace PowerLab

#endif // CIRCUITELEMENTVIEW_H
