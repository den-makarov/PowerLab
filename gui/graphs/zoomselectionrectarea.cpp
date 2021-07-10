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

bool ZoomSelectionRectArea::isActive() const {
  return QRubberBand::isVisible();
}

void ZoomSelectionRectArea::hide() {
  QRubberBand::hide();
}

QRect ZoomSelectionRectArea::getGlobalArea() const {
  return geometry();
}

QRect ZoomSelectionRectArea::getLocalArea() const {
  QPoint origin(m_localOrigin);
  if(geometry().x() < m_globalOrigin.x()) {
    origin.setX(origin.x() - geometry().width() + 1);
  }

  if(geometry().y() < m_globalOrigin.y()) {
    origin.setY(origin.y() - geometry().height() + 1);
  }

  QRect shiftedArea(origin, geometry().size());

  if(shiftedArea.width() == 0) {
    shiftedArea.setWidth(1);
  }

  if(shiftedArea.height() == 0) {
    shiftedArea.setHeight(1);
  }

  return shiftedArea;
}

void ZoomSelectionRectArea::setAreaOrigin(QPoint globalPos, QPoint localPos) {
  m_globalOrigin = globalPos;
  m_localOrigin = localPos;
  setGeometry(QRect(m_globalOrigin, QSize()));
}

void ZoomSelectionRectArea::updateArea(QPoint point) {
  setGeometry(QRect(m_globalOrigin, point).normalized());
}

} // namespace Gui
} // namespace PowerLab
