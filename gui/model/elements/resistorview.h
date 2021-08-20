#ifndef RESISTORVIEW_H
#define RESISTORVIEW_H

#include "gui/model/circuitelementview.h"

namespace PowerLab {
namespace Gui {

class ResistorView : public CircuitElementView {
public:
  ResistorView(ModelDesign::Element element);
  virtual QRectF boundingRect() const override;
  virtual QPainterPath shape() const override;

private:
  static constexpr qreal BODY_HEIGHT = 20;
  static constexpr qreal BODY_WIDTH = 50;

  virtual void paintElement(QPainter* painter, qreal levelOfDetails) const override;
  virtual void drawText(QPainter *painter, qreal levelOfDetails) const override;
};

} // namespace Gui
} // namespace PowerLab

#endif // RESISTORVIEW_H
