#ifndef DRAWINGITEM_H
#define DRAWINGITEM_H

#include <QGraphicsItem>

namespace PowerLab {
namespace Gui {

class DrawingItem : public QGraphicsItem {
public:
  DrawingItem(QGraphicsItem* parent = nullptr);
};

} // namespace Gui
} // namespace PowerLab

#endif // DRAWINGITEM_H
