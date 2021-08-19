#ifndef INDUCTORVIEW_H
#define INDUCTORVIEW_H

#include "gui/model/circuitelementview.h"

namespace PowerLab {
namespace Gui {

class InductorView : public CircuitElementView {
public:
  InductorView(ModelDesign::Element element, QPoint position);
  virtual QRectF boundingRect() const override;
  virtual QPainterPath shape() const override;

private:
  virtual void paintElement(QPainter* painter, qreal levelOfDetails) const override;
  virtual void drawText(QPainter *painter, qreal levelOfDetails) const override;
};

} // namespace Gui
} // namespace PowerLab

#endif // INDUCTORVIEW_H
