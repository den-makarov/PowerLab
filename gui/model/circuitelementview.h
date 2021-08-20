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
  explicit CircuitElementView(ModelDesign::Element element);

  virtual QRectF boundingRect() const override = 0;
  virtual QPainterPath shape() const override = 0;

  void paint(QPainter *painter,
             const QStyleOptionGraphicsItem *item,
             QWidget *widget) override;

protected:
  static constexpr qreal PIN_WIDTH = 20;

  virtual void paintElement(QPainter *painter, qreal levelOfDetails) const = 0;
  virtual void drawText(QPainter *painter, qreal levelOfDetails) const = 0;

  ModelDesign::Element& getElement();
  const ModelDesign::Element& getElement() const;

private:
  ModelDesign::Element m_element;
  QColor m_color = Qt::white;
};

} // namespace Gui
} // namespace PowerLab

#endif // CIRCUITELEMENTVIEW_H
