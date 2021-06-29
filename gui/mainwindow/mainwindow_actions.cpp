#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include "mainwindow/mainwindow.h"

namespace PowerLab {
namespace Gui {

void MainWindow::createActions() {
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  QToolBar* fileToolBar = addToolBar(tr("File"));
  const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
  QAction* newAct = new QAction(newIcon, tr("&New"), this);
//  newAct->setShortcuts(QKeySequence::New);
  newAct->setStatusTip(tr("Create a new file"));
  connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
  fileMenu->addAction(newAct);
  fileToolBar->addAction(newAct);

  const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
  QAction* openAct = new QAction(openIcon, tr("&Open..."), this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open an existing file"));
  connect(openAct, &QAction::triggered, this, &MainWindow::open);
  fileMenu->addAction(openAct);
  fileToolBar->addAction(openAct);

  const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
  QAction* saveAct = new QAction(saveIcon, tr("&Save"), this);
  saveAct->setShortcuts(QKeySequence::Save);
  saveAct->setStatusTip(tr("Save the document to disk"));
  connect(saveAct, &QAction::triggered, this, &MainWindow::save);
  fileMenu->addAction(saveAct);
  fileToolBar->addAction(saveAct);

  const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
  QAction* saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
  saveAsAct->setShortcuts(QKeySequence::SaveAs);
  saveAsAct->setStatusTip(tr("Save the document under a new name"));

  fileMenu->addSeparator();

  const QIcon exitIcon = QIcon::fromTheme("application-exit");
  QAction* exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));

  QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
  QToolBar* editToolBar = addToolBar(tr("Edit"));

  const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
  QAction* cutAct = new QAction(cutIcon, tr("Cu&t"), this);

  cutAct->setShortcuts(QKeySequence::Cut);
  cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                          "clipboard"));
//    connect(cutAct, &QAction::triggered, textEdit, &QPlainTextEdit::cut);
  editMenu->addAction(cutAct);
  editToolBar->addAction(cutAct);

  const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
  QAction* copyAct = new QAction(copyIcon, tr("&Copy"), this);
  copyAct->setShortcuts(QKeySequence::Copy);
  copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                           "clipboard"));
//    connect(copyAct, &QAction::triggered, textEdit, &QPlainTextEdit::copy);
  editMenu->addAction(copyAct);
  editToolBar->addAction(copyAct);

  const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
  QAction* pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
  pasteAct->setShortcuts(QKeySequence::Paste);
  pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                            "selection"));
//    connect(pasteAct, &QAction::triggered, textEdit, &QPlainTextEdit::paste);
  editMenu->addAction(pasteAct);
  editToolBar->addAction(pasteAct);

  QToolBar* modelToolBar = addToolBar(tr("Model"));
  const QIcon addIcon = QIcon::fromTheme("edit-add", QIcon(":/images/add.png"));
  m_addGraphAction = new QAction(addIcon, tr("&Add"), this);
  m_addGraphAction->setShortcuts(QKeySequence::New);
  m_addGraphAction->setStatusTip(tr("Select signals to plot new graph"));
  modelToolBar->addAction(m_addGraphAction);
  m_addGraphAction->setDisabled(true);
  connect(m_addGraphAction, &QAction::triggered, this, [this](){
    if(this->m_modelResult) {
      this->showMetaData(true, "");
    }
  });

  // @TODO: Find correct icon fallback path
  const QIcon parametersIcon = QIcon::fromTheme("system-settings", QIcon(":/images/settings.png"));
  QAction* showParams = new QAction(parametersIcon, tr("&Parameters"), this);
  showParams->setShortcuts(QKeySequence::Preferences);
  showParams->setStatusTip(tr("Show parameters to configure component, design or graph"));
  modelToolBar->addAction(showParams);
  connect(showParams, &QAction::triggered, this, [this](){
    this->showParameters();
  });

  // @TODO: Find correct icon fallback path
  const QIcon libraryIcon = QIcon::fromTheme("extensions", QIcon(":/images/extensions.png"));
  QAction* showLib = new QAction(libraryIcon, tr("&Library"), this);
  showLib->setShortcuts(QKeySequence::Backspace);
  showLib->setStatusTip(tr("Show library to chose and add components to model"));
  modelToolBar->addAction(showLib);

  connect(showLib, &QAction::triggered, this, [this](){
    this->showLibrary();
  });

  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  QAction* aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
  aboutAct->setStatusTip(tr("Show the application's About box"));

  cutAct->setEnabled(false);
  copyAct->setEnabled(false);
//    connect(textEdit, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
//    connect(textEdit, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
}

} // namespace Gui
} // namespace PowerLab
