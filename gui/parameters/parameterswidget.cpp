#include "parameterswidget.h"

namespace PowerLab {
namespace Gui {

ParametersWidget::ParametersWidget(QWidget *parent)
  : QWidget(parent)
{
  // EMPTY
}

QSize ParametersWidget::sizeHint() const {
  return QSize(PREFERRED_WIDGIT_WIDTH_HINT, PREFERRED_WIDGIT_HEIGHT_HINT);
}

} // namespace Gui
} // namespace PowerLab
