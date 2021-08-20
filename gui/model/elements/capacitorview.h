#ifndef CAPACITORVIEW_H
#define CAPACITORVIEW_H

#include "gui/model/circuitelementview.h"

namespace PowerLab {
namespace Gui {

class CapacitorView : public CircuitElementView {
public:
  CapacitorView(ModelDesign::Element element);
  virtual QRectF boundingRect() const override;
  virtual QPainterPath shape() const override;

private:
  virtual void paintElement(QPainter* painter, qreal levelOfDetails) const override;
  virtual void drawText(QPainter *painter, qreal levelOfDetails) const override;
};

} // namespace Gui
} // namespace PowerLab

#endif // CAPACITORVIEW_H
