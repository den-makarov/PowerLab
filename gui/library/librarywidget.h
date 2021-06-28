#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

namespace PowerLab {
namespace Gui {

class LibraryWidget : public QWidget {
  Q_OBJECT
public:
  explicit LibraryWidget(QWidget *parent = nullptr);

signals:

};

} // namespace Gui
} // namespace PowerLab

#endif // LIBRARYWIDGET_H
