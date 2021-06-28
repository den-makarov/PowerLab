#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>

namespace PowerLab {
namespace Gui {

class ModelWidget : public QWidget {
  Q_OBJECT
public:
  explicit ModelWidget(QWidget *parent = nullptr, const QString& title = "untitled");

signals:

};

} // namespace Gui
} // namespace PowerLab

#endif // MODELWIDGET_H
