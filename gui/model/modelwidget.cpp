#include <QGraphicsScene>
#include <QGraphicsItem>

#include "modelwidget.h"
#include "modeldesign/model.h"

namespace PowerLab {
namespace Gui {

ModelWidget::ModelWidget(QWidget *parent, const QString& title)
  : QWidget(parent)
  , m_scene(new QGraphicsScene(this))
{
  setToolTip(tr("Model Design"));
  setWindowTitle(title);
  auto model = std::make_unique<ModelDesign::Model>("test");
}

} // namespace Gui
} // namespace PowerLab
