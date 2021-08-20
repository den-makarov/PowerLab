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
    QGraphicsItem* item = new ResistorView(R1);
    item->setPos(QPointF(0, 30));
    m_scene->addItem(item);
  }

  auto C1 = model->getElement("C1");
  if(C1) {
    QGraphicsItem* item = new CapacitorView(C1);
    item->setPos(QPointF(0, 0));
    m_scene->addItem(item);
  }

  auto L1 = model->getElement("L1");
  if(L1) {
    QGraphicsItem* item = new InductorView(L1);
    item->setPos(QPointF(0, -20));
    m_scene->addItem(item);
  }

  auto AC1 = model->getElement("VA1");
  if(AC1) {
    QGraphicsItem* item = new ACVoltageView(AC1);
    item->setPos(QPointF(80, 0));
    m_scene->addItem(item);

    item = new DiodeView(AC1);
    item->setPos(QPointF(-80, 0));
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
    zoomInIcon->setIcon(QPixmap(":/images/zoom_in.png"));
    zoomInIcon->setIconSize(iconSize);
    QToolButton *zoomOutIcon = new QToolButton;
    zoomOutIcon->setAutoRepeat(true);
    zoomOutIcon->setAutoRepeatInterval(33);
    zoomOutIcon->setAutoRepeatDelay(0);
    zoomOutIcon->setIcon(QPixmap(":/images/zoom_out.png"));
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
    labelLayout->addWidget(printButton);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);
    setLayout(topLayout);

    connect(zoomSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);
    connect(selectModeButton, &QAbstractButton::toggled, this, &View::togglePointerMode);
    connect(dragModeButton, &QAbstractButton::toggled, this, &View::togglePointerMode);
    connect(zoomInIcon, &QAbstractButton::clicked, this, &View::zoomIn);
    connect(zoomOutIcon, &QAbstractButton::clicked, this, &View::zoomOut);
    connect(printButton, &QAbstractButton::clicked, this, &View::print);

    setupMatrix();
    graphicsView->setRenderHint(QPainter::Antialiasing, true);
}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));
    QTransform matrix;
    matrix.scale(scale, scale);
    graphicsView->setTransform(matrix);
}

void View::togglePointerMode()
{
    graphicsView->setDragMode(selectModeButton->isChecked()
                              ? QGraphicsView::RubberBandDrag
                              : QGraphicsView::ScrollHandDrag);
    graphicsView->setInteractive(selectModeButton->isChecked());
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
    zoomSlider->setValue(zoomSlider->value() + level + 1);
}

void View::zoomOut(int level)
{
    zoomSlider->setValue(zoomSlider->value() - level - 1);
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

