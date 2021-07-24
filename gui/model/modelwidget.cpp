#include <QGraphicsScene>
#include <QGraphicsItem>

#include "modelwidget.h"

namespace PowerLab {
namespace Gui {

ModelWidget::ModelWidget(QWidget *parent, const QString& title)
  : QWidget(parent)
  , m_scene(new QGraphicsScene(this))
{
  setToolTip(tr("Model Design"));
  setWindowTitle(title);
}

} // namespace Gui
} // namespace PowerLab
