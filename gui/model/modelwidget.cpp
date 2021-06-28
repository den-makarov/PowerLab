#include "modelwidget.h"

namespace PowerLab {
namespace Gui {

ModelWidget::ModelWidget(QWidget *parent, const QString& title) : QWidget(parent) {
  setToolTip(tr("Model Design"));
  setWindowTitle(title);
}

} // namespace Gui
} // namespace PowerLab
