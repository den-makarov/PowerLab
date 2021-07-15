#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QWidget>

namespace PowerLab {
namespace Gui {

class ParametersWidget : public QWidget {
  Q_OBJECT
public:
  explicit ParametersWidget(QWidget *parent = nullptr);

  QSize sizeHint() const;

private:
  constexpr static int PREFERRED_WIDGIT_WIDTH_HINT = 200;
  constexpr static int PREFERRED_WIDGIT_HEIGHT_HINT = 1000;
};

} // namespace Gui
} // namespace PowerLab

#endif // PARAMETERSWIDGET_H
