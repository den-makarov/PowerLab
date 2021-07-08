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
  QRect getGlobalArea() const;
  QRect getLocalArea() const;
  void setAreaOrigin(QPoint globalPos, QPoint localPos = QPoint(0, 0));
  void updateArea(QPoint point);

private:
  QPoint m_globalOrigin;
  QPoint m_localOrigin;
};

} // namespace Gui
} // namespace PowerLab

#endif // ZOOMSELECTIONRECTAREA_H
