#include "zoomselectionrectarea.h"

namespace PowerLab {
namespace Gui {

ZoomSelectionRectArea::ZoomSelectionRectArea()
  : QRubberBand(QRubberBand::Rectangle)
{
  setWindowOpacity(0.5);
}

void ZoomSelectionRectArea::show() {
  QRubberBand::show();
}

void ZoomSelectionRectArea::hide() {
  QRubberBand::hide();
}

QRect ZoomSelectionRectArea::getArea() const {
  return geometry().normalized();
}

void ZoomSelectionRectArea::setAreaOrigin(QPoint origin) {
  m_origin = origin;
  setGeometry(QRect(m_origin, QSize()));
}

void ZoomSelectionRectArea::updateArea(QPoint point) {
  setGeometry(QRect(m_origin, point).normalized());
}

QRect ZoomSelectionRectArea::getAreaNormalized(QPoint shiftPoint) const {
  QRect shiftedArea(shiftPoint, geometry().size());
  return shiftedArea.normalized();
}

} // namespace Gui
} // namespace PowerLab
