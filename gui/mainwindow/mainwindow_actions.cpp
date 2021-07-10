#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include "mainwindow/mainwindow.h"

namespace PowerLab {
namespace Gui {

void MainWindow::createActions() {
  // @NOTE: Order is matter
  createFileActions();
  createEditActions();
  createHelpActions();
  createGraphActions();
  createZoomActions();
}

void MainWindow::createZoomActions() {
  QToolBar* zoomToolBar = addToolBar(tr("Zoom"));

  const QIcon zoomEnabledIcon = QIcon::fromTheme("search-symbolic", QIcon(":/images/zoom-enabled.png"));
  QAction* zoomEnabled = new QAction(zoomEnabledIcon, tr("Zoom enable"), this);
  zoomEnabled->setCheckable(true);
  zoomEnabled->setStatusTip(tr("Zoom enable/disable"));
  zoomToolBar->addAction(zoomEnabled);

  connect(zoomEnabled, &QAction::toggled, this, [this](bool checked){
    this->zoomEnableHandler(checked);
  });

  const QIcon zoomInIcon = QIcon::fromTheme("zoom-in", QIcon(":/images/zoom-in.png"));
  QAction* zoomIn = new QAction(zoomInIcon, tr("Zoom in"), this);
  zoomIn->setShortcuts(QKeySequence::ZoomIn);
  zoomIn->setStatusTip(tr("Zoom in"));
  zoomToolBar->addAction(zoomIn);

  connect(zoomIn, &QAction::triggered, this, [this](){
    this->zoomInHandler();
  });

  const QIcon zoomResetIcon = QIcon::fromTheme("zoom-original", QIcon(":/images/zoom-original.png"));
  QAction* zoomReset = new QAction(zoomResetIcon, tr("Zoom reset"), this);
  zoomReset->setStatusTip(tr("Zoom out"));
  zoomToolBar->addAction(zoomReset);

  connect(zoomReset, &QAction::triggered, this, [this](){
    this->zoomResetHandler();
  });

  const QIcon zoomOutIcon = QIcon::fromTheme("zoom-out", QIcon(":/images/zoom-out.png"));
  QAction* zoomOut = new QAction(zoomOutIcon, tr("Zoom out"), this);
  zoomOut->setShortcuts(QKeySequence::ZoomOut);
  zoomOut->setStatusTip(tr("Zoom out"));
  zoomToolBar->addAction(zoomOut);

  connect(zoomOut, &QAction::triggered, this, [this](){
    this->zoomOutHandler();
  });

  // @TODO: It shouldn't be triggered by any file opened.
  // Consider to use signal when model design or graph widget is active
  connect(this, &MainWindow::fileOpened, [zoomToolBar](QString){
    zoomToolBar->setEnabled(true);
  });

  zoomToolBar->setEnabled(false);
}

void MainWindow::createEditActions() {
  QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
  QToolBar* editToolBar = addToolBar(tr("Edit"));

  const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
  QAction* cutAct = new QAction(cutIcon, tr("Cu&t"), this);
  cutAct->setShortcuts(QKeySequence::Cut);
  cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                          "clipboard"));
  cutAct->setEnabled(false);
  editMenu->addAction(cutAct);
  editToolBar->addAction(cutAct);
  // @TODO: Implement cut handler

  const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
  QAction* copyAct = new QAction(copyIcon, tr("&Copy"), this);
  copyAct->setShortcuts(QKeySequence::Copy);
  copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                           "clipboard"));
  copyAct->setEnabled(false);
  editMenu->addAction(copyAct);
  editToolBar->addAction(copyAct);
  // @TODO: Implement copy handler

  const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
  QAction* pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
  pasteAct->setShortcuts(QKeySequence::Paste);
  pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                            "selection"));
  editMenu->addAction(pasteAct);
  editToolBar->addAction(pasteAct);
  // @TODO: Implement paste handler
}

void MainWindow::createFileActions() {
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  QToolBar* fileToolBar = addToolBar(tr("File"));

  const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
  QAction* newAct = new QAction(newIcon, tr("&New"), this);
  newAct->setShortcuts(QKeySequence::New);
  newAct->setStatusTip(tr("Create a new file"));
  fileMenu->addAction(newAct);
  fileToolBar->addAction(newAct);

  connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

  const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
  QAction* openAct = new QAction(openIcon, tr("&Open..."), this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open an existing file"));
  fileMenu->addAction(openAct);
  fileToolBar->addAction(openAct);

  connect(openAct, &QAction::triggered, this, &MainWindow::open);

  const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
  QAction* saveAct = new QAction(saveIcon, tr("&Save"), this);
  saveAct->setShortcuts(QKeySequence::Save);
  saveAct->setStatusTip(tr("Save the document to disk"));
  fileMenu->addAction(saveAct);
  fileToolBar->addAction(saveAct);

  connect(saveAct, &QAction::triggered, this, &MainWindow::save);

  const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
  QAction* saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
  saveAsAct->setShortcuts(QKeySequence::SaveAs);
  saveAsAct->setStatusTip(tr("Save the document under a new name"));

  fileMenu->addSeparator();

  const QIcon exitIcon = QIcon::fromTheme("application-exit");
  QAction* exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));
}

void MainWindow::createGraphActions() {
  QToolBar* graphToolBar = addToolBar(tr("Graph"));

  const QIcon addIcon = QIcon::fromTheme("edit-add", QIcon(":/images/add.png"));
  m_addGraphAction = new QAction(addIcon, tr("Add"), this);
  m_addGraphAction->setStatusTip(tr("Select signals to plot new graph"));
  m_addGraphAction->setDisabled(true);
  graphToolBar->addAction(m_addGraphAction);

  connect(m_addGraphAction, &QAction::triggered, this, [this](){
    if(this->m_modelResult) {
      this->showMetaData(true, "");
    }
  });

  // @TODO: Find correct icon fallback path
  const QIcon parametersIcon = QIcon::fromTheme("document-properties", QIcon(":/images/settings.png"));
  QAction* showParams = new QAction(parametersIcon, tr("Parameters"), this);
  showParams->setShortcuts(QKeySequence::Preferences);
  showParams->setStatusTip(tr("Show parameters to configure component, design or graph"));
  graphToolBar->addAction(showParams);

  connect(showParams, &QAction::triggered, this, [this](){
    this->showParameters();
  });

  // @TODO: Find correct icon fallback path
  const QIcon libraryIcon = QIcon::fromTheme("extensions", QIcon(":/images/extensions.png"));
  QAction* showLib = new QAction(libraryIcon, tr("Library"), this);
  showLib->setShortcuts(QKeySequence::Backspace);
  showLib->setStatusTip(tr("Show library to chose and add components to model"));
  graphToolBar->addAction(showLib);

  connect(showLib, &QAction::triggered, this, [this](){
    this->showLibrary();
  });
}

void MainWindow::createHelpActions() {
  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  QAction* aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
  aboutAct->setStatusTip(tr("Show the application's About box"));
}

} // namespace Gui
} // namespace PowerLab
