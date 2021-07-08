#ifndef ZOOMSELECTIONRECTAREA_H
#define ZOOMSELECTIONRECTAREA_H

#include <QRubberBand>

namespace PowerLab {
namespace Gui {

class ZoomSelectionRectArea : private QRubberBand {
public:
  ZoomSelectionRectArea();

  void show();
  void hide();
  QRect getArea() const;
  QRect getAreaNormalized(QPoint shiftPoint) const;
  void setAreaOrigin(QPoint origin);
  void updateArea(QPoint point);

private:
  QPoint m_origin;
};

} // namespace Gui
} // namespace PowerLab

#endif // ZOOMSELECTIONRECTAREA_H
