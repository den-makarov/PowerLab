#ifndef DIODEVIEW_H
#define DIODEVIEW_H

#include "gui/model/circuitelementview.h"

namespace PowerLab {
namespace Gui {

class DiodeView : public CircuitElementView {
public:
  DiodeView(ModelDesign::Element element, QPoint position);
  virtual QRectF boundingRect() const override;
  virtual QPainterPath shape() const override;

private:
  virtual void paintElement(QPainter* painter, qreal levelOfDetails) const override;
  virtual void drawText(QPainter *painter, qreal levelOfDetails) const override;
};

} // namespace Gui
} // namespace PowerLab

#endif // DIODEVIEW_H
