#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QSplitter>

#include "modelwidget.h"
#include "modeldesign/model.h"
#include "elements/resistorview.h"
#include "elements/capacitorview.h"
#include "elements/inductorview.h"
#include "elements/acvoltageview.h"
#include "elements/diodeview.h"

namespace PowerLab {
namespace Gui {

ModelWidget::ModelWidget(QWidget *parent, const QString& title)
  : QWidget(parent)
  , m_scene(new QGraphicsScene(this))
  , h1Splitter(new QSplitter(this))
  , h2Splitter(new QSplitter(this))
{
  setToolTip(tr("Model Design"));
  setWindowTitle(title);
  auto model = std::make_unique<ModelDesign::Model>("test");

  auto R1 = model->getElement("R1");
  if(R1) {
    QGraphicsItem* item = new ResistorView(R1, QPoint(0, 0));
    item->setPos(QPointF(0, 0));
    m_scene->addItem(item);
  }

  auto C1 = model->getElement("C1");
  if(C1) {
    QGraphicsItem* item = new CapacitorView(C1, QPoint(80, 0));
    item->setPos(QPointF(0, 0));
    m_scene->addItem(item);
  }

  auto L1 = model->getElement("L1");
  if(L1) {
    QGraphicsItem* item = new InductorView(L1, QPoint(0, 40));
    item->setPos(QPointF(0, 0));
    m_scene->addItem(item);
  }

  auto AC1 = model->getElement("VA1");
  if(AC1) {
    QGraphicsItem* item = new ACVoltageView(AC1, QPoint(80, 40));
    item->setPos(QPointF(0, 0));
    m_scene->addItem(item);

    item = new DiodeView(AC1, QPoint(160, 40));
    item->setPos(QPointF(0, 0));
    m_scene->addItem(item);
  }
//  QSplitter* vSplitter = new QSplitter;
//  vSplitter->setOrientation(Qt::Vertical);
//  vSplitter->addWidget(h1Splitter);
//  vSplitter->addWidget(h2Splitter);

  View *view = new View("Top left view");
  view->view()->setScene(m_scene);
//  h1Splitter->addWidget(view);

//  view = new View("Top right view");
//  view->view()->setScene(m_scene);
//  h1Splitter->addWidget(view);

//  view = new View("Bottom left view");
//  view->view()->setScene(m_scene);
//  h2Splitter->addWidget(view);

//  view = new View("Bottom right view");
//  view->view()->setScene(m_scene);
//  h2Splitter->addWidget(view);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(view);
  setLayout(layout);
}

} // namespace Gui
} // namespace PowerLab

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif
#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#else
#include <QtWidgets>
#endif
#include <QtMath>

#if QT_CONFIG(wheelevent)
void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->angleDelta().y() > 0)
            view->zoomIn(6);
        else
            view->zoomOut(6);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}
#endif

View::View(const QString &name, QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    QToolButton *zoomInIcon = new QToolButton;
    zoomInIcon->setAutoRepeat(true);
    zoomInIcon->setAutoRepeatInterval(33);
    zoomInIcon->setAutoRepeatDelay(0);
    zoomInIcon->setIcon(QPixmap(":/zoomin.png"));
    zoomInIcon->setIconSize(iconSize);
    QToolButton *zoomOutIcon = new QToolButton;
    zoomOutIcon->setAutoRepeat(true);
    zoomOutIcon->setAutoRepeatInterval(33);
    zoomOutIcon->setAutoRepeatDelay(0);
    zoomOutIcon->setIcon(QPixmap(":/zoomout.png"));
    zoomOutIcon->setIconSize(iconSize);
    zoomSlider = new QSlider;
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);

    // Zoom slider layout
    QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
    zoomSliderLayout->addWidget(zoomInIcon);
    zoomSliderLayout->addWidget(zoomSlider);
    zoomSliderLayout->addWidget(zoomOutIcon);

    QToolButton *rotateLeftIcon = new QToolButton;
    rotateLeftIcon->setIcon(QPixmap(":/rotateleft.png"));
    rotateLeftIcon->setIconSize(iconSize);
    QToolButton *rotateRightIcon = new QToolButton;
    rotateRightIcon->setIcon(QPixmap(":/rotateright.png"));
    rotateRightIcon->setIconSize(iconSize);
    rotateSlider = new QSlider;
    rotateSlider->setOrientation(Qt::Horizontal);
    rotateSlider->setMinimum(-360);
    rotateSlider->setMaximum(360);
    rotateSlider->setValue(0);
    rotateSlider->setTickPosition(QSlider::TicksBelow);

    // Rotate slider layout
    QHBoxLayout *rotateSliderLayout = new QHBoxLayout;
    rotateSliderLayout->addWidget(rotateLeftIcon);
    rotateSliderLayout->addWidget(rotateSlider);
    rotateSliderLayout->addWidget(rotateRightIcon);

    resetButton = new QToolButton;
    resetButton->setText(tr("0"));
    resetButton->setEnabled(false);

    // Label layout
    QHBoxLayout *labelLayout = new QHBoxLayout;
    label = new QLabel(name);
    label2 = new QLabel(tr("Pointer Mode"));
    selectModeButton = new QToolButton;
    selectModeButton->setText(tr("Select"));
    selectModeButton->setCheckable(true);
    selectModeButton->setChecked(true);
    dragModeButton = new QToolButton;
    dragModeButton->setText(tr("Drag"));
    dragModeButton->setCheckable(true);
    dragModeButton->setChecked(false);
    antialiasButton = new QToolButton;
    antialiasButton->setText(tr("Antialiasing"));
    antialiasButton->setCheckable(true);
    antialiasButton->setChecked(false);
    openGlButton = new QToolButton;
    openGlButton->setText(tr("OpenGL"));
    openGlButton->setCheckable(true);
#ifndef QT_NO_OPENGL
    openGlButton->setEnabled(QGLFormat::hasOpenGL());
#else
    openGlButton->setEnabled(false);
#endif
    printButton = new QToolButton;
    printButton->setIcon(QIcon(QPixmap(":/fileprint.png")));

    QButtonGroup *pointerModeGroup = new QButtonGroup(this);
    pointerModeGroup->setExclusive(true);
    pointerModeGroup->addButton(selectModeButton);
    pointerModeGroup->addButton(dragModeButton);

    labelLayout->addWidget(label);
    labelLayout->addStretch();
    labelLayout->addWidget(label2);
    labelLayout->addWidget(selectModeButton);
    labelLayout->addWidget(dragModeButton);
    labelLayout->addStretch();
    labelLayout->addWidget(antialiasButton);
    labelLayout->addWidget(openGlButton);
    labelLayout->addWidget(printButton);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);
    topLayout->addLayout(rotateSliderLayout, 2, 0);
    topLayout->addWidget(resetButton, 2, 1);
    setLayout(topLayout);

    connect(resetButton, &QAbstractButton::clicked, this, &View::resetView);
    connect(zoomSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);
    connect(rotateSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);
    connect(graphicsView->verticalScrollBar(), &QAbstractSlider::valueChanged,
            this, &View::setResetButtonEnabled);
    connect(graphicsView->horizontalScrollBar(), &QAbstractSlider::valueChanged,
            this, &View::setResetButtonEnabled);
    connect(selectModeButton, &QAbstractButton::toggled, this, &View::togglePointerMode);
    connect(dragModeButton, &QAbstractButton::toggled, this, &View::togglePointerMode);
    connect(antialiasButton, &QAbstractButton::toggled, this, &View::toggleAntialiasing);
    connect(openGlButton, &QAbstractButton::toggled, this, &View::toggleOpenGL);
    connect(rotateLeftIcon, &QAbstractButton::clicked, this, &View::rotateLeft);
    connect(rotateRightIcon, &QAbstractButton::clicked, this, &View::rotateRight);
    connect(zoomInIcon, &QAbstractButton::clicked, this, &View::zoomIn);
    connect(zoomOutIcon, &QAbstractButton::clicked, this, &View::zoomOut);
    connect(printButton, &QAbstractButton::clicked, this, &View::print);

    setupMatrix();
}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView()
{
    zoomSlider->setValue(250);
    rotateSlider->setValue(0);
    setupMatrix();
    graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

    resetButton->setEnabled(false);
}

void View::setResetButtonEnabled()
{
    resetButton->setEnabled(true);
}

void View::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    QTransform matrix;
    matrix.scale(scale, scale);
    matrix.rotate(rotateSlider->value());

    graphicsView->setTransform(matrix);
    setResetButtonEnabled();
}

void View::togglePointerMode()
{
    graphicsView->setDragMode(selectModeButton->isChecked()
                              ? QGraphicsView::RubberBandDrag
                              : QGraphicsView::ScrollHandDrag);
    graphicsView->setInteractive(selectModeButton->isChecked());
}

void View::toggleOpenGL()
{
#ifndef QT_NO_OPENGL
    graphicsView->setViewport(openGlButton->isChecked() ? new QGLWidget(QGLFormat(QGL::SampleBuffers)) : new QWidget);
#endif
}

void View::toggleAntialiasing()
{
    graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
}

void View::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        graphicsView->render(&painter);
    }
#endif
}

void View::zoomIn(int level)
{
    zoomSlider->setValue(zoomSlider->value() + level);
}

void View::zoomOut(int level)
{
    zoomSlider->setValue(zoomSlider->value() - level);
}

void View::rotateLeft()
{
    rotateSlider->setValue(rotateSlider->value() - 10);
}

void View::rotateRight()
{
    rotateSlider->setValue(rotateSlider->value() + 10);
}

//void PaintLines() {
  //    // Draw red ink
  //    if (m_stuff.size() > 1) {
  //        QPen p = painter->pen();
  //        painter->setPen(QPen(Qt::red,
  //                             1,
  //                             Qt::SolidLine,
  //                             Qt::RoundCap,
  //                             Qt::RoundJoin));
  //        painter->setBrush(Qt::NoBrush);
  //        QPainterPath path;
  //        path.moveTo(m_stuff.first());
  //        for (int i = 1; i < m_stuff.size(); ++i)
  //            path.lineTo(m_stuff.at(i));
  //        painter->drawPath(path);
  //        painter->setPen(p);
  //    }
//}

//void PaintLines::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
//    if (event->modifiers() & Qt::ShiftModifier) {
//        m_stuff << event->pos();
//        update();
//        return;
//    }
//    QGraphicsItem::mouseMoveEvent(event);
//    update();
//}

