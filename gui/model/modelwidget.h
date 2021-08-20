#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>

class QGraphicsScene;
class QSplitter;

namespace PowerLab {
namespace Gui {

class ModelWidget : public QWidget {
  Q_OBJECT
public:
  explicit ModelWidget(QWidget *parent = nullptr, const QString& title = "untitled");

signals:

private:
  QGraphicsScene* m_scene = nullptr;
  QSplitter* h1Splitter;
  QSplitter* h2Splitter;
};

} // namespace Gui
} // namespace PowerLab

#include <QFrame>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *) override;
#endif

private:
    View *view;
};

class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(const QString &name, QWidget *parent = nullptr);

    QGraphicsView *view() const;

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

private slots:
    void setupMatrix();
    void togglePointerMode();
    void print();

private:
    GraphicsView *graphicsView;
    QLabel *label;
    QLabel *label2;
    QToolButton *selectModeButton;
    QToolButton *dragModeButton;
    QToolButton *printButton;
    QSlider *zoomSlider;
};

#endif // MODELWIDGET_H
