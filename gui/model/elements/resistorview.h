#ifndef RESISTORVIEW_H
#define RESISTORVIEW_H

#include "gui/model/circuitelementview.h"

namespace PowerLab {
namespace Gui {

class ResistorView : public CircuitElementView {
public:
  ResistorView(ModelDesign::Element element, QPoint position);
private:
  virtual void paintElement(QPainter* painter, qreal levelOfDetails) const override;
};

} // namespace Gui
} // namespace PowerLab

#endif // RESISTORVIEW_H
