#ifndef DRAWINGITEM_H
#define DRAWINGITEM_H

#include <QGraphicsItem>

namespace PowerLab {
namespace Gui {

class DrawingItem : public QGraphicsItem {
  Q_OBJECT
public:
  DrawingItem(DrawingItem* parent = nullptr);
};

} // namespace Gui
} // namespace PowerLab

#endif // DRAWINGITEM_H
