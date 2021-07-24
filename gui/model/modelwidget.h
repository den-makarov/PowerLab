#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>

class QGraphicsScene;

namespace PowerLab {
namespace Gui {

class ModelWidget : public QWidget {
  Q_OBJECT
public:
  explicit ModelWidget(QWidget *parent = nullptr, const QString& title = "untitled");

signals:

private:
  QGraphicsScene* m_scene = nullptr;
};

} // namespace Gui
} // namespace PowerLab

#endif // MODELWIDGET_H
