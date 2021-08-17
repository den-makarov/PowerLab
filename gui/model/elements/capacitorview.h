#ifndef CAPACITORVIEW_H
#define CAPACITORVIEW_H

#include "gui/model/circuitelementview.h"

namespace PowerLab {
namespace Gui {

class CapacitorView : public CircuitElementView {
public:
  CapacitorView(ModelDesign::Element element, QPoint position);
private:
  virtual void paintElement(QPainter* painter, qreal levelOfDetails) const override;
};

} // namespace Gui
} // namespace PowerLab

#endif // CAPACITORVIEW_H
