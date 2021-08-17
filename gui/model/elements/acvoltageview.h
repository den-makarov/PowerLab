#ifndef ACVOLTAGEVIEW_H
#define ACVOLTAGEVIEW_H

#include "gui/model/circuitelementview.h"

namespace PowerLab {
namespace Gui {

class ACVoltageView : public CircuitElementView {
public:
  ACVoltageView(ModelDesign::Element element, QPoint position);
private:
  virtual void paintElement(QPainter* painter, qreal levelOfDetails) const override;
};

} // namespace Gui
} // namespace PowerLab

#endif // ACVOLTAGEVIEW_H
