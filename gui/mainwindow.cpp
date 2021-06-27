#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QGridLayout>
#include <QKeySequence>
#include <QStatusBar>
#include <QToolBar>
#include <QThread>
#include <QTimer>
#include <QAbstractItemModel>
#include <QtWidgets>

#include "logger.h"
#include "modelresult/modelresultvalidator.h"
#include "modelresult/modelresultmeta.h"
#include "dialogs/metadatawindow.h"
#include "graphs/graphwidget.h"
#include "mainwindow.h"

namespace Gui {

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{ 
  setWindowState(Qt::WindowState::WindowMaximized);

  createActions();
  createStatusBar();
  addDefaultModelDesignWidget();
  setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowTabbedDocks | QMainWindow::AllowNestedDocks);
  readSettings();

  QGuiApplication::setFallbackSessionManagementEnabled(false);
  connect(qApp, &QGuiApplication::commitDataRequest,
          this, &MainWindow::commitData);

  setCurrentFile(QString());
  setUnifiedTitleAndToolBarOnMac(true);

  m_metaDataWindow = new QMessageBox(this);
}

void MainWindow::closeEvent(QCloseEvent* event) {
  if(maybeSave()) {
    writeSettings();
    event->accept();
  } else {
    event->ignore();
  }
}

void MainWindow::newFile() {
  if(maybeSave()) {
    setCurrentFile(QString());
  }
}

void MainWindow::open() {
  if(maybeSave()) {
    auto dialogTitle = tr("Open file with modeling results");
    auto dialogFilter = tr("Modeling result files (*.esk *.dat)");
    QString filename = QFileDialog::getOpenFileName(this, dialogTitle, "", dialogFilter);

    if(!filename.isEmpty()) {
      openModelResults(filename);
    }
  }
}

bool MainWindow::save() {
  if (m_currentFile.isEmpty()) {
    return saveAs();
  } else {
    return saveFile(m_currentFile);
  }
}

bool MainWindow::saveAs() {
  return false;
//    QFileDialog dialog(this);
//    dialog.setWindowModality(Qt::WindowModal);
//    dialog.setAcceptMode(QFileDialog::AcceptSave);
//    if (dialog.exec() != QDialog::Accepted)
//        return false;
//    return saveFile(dialog.selectedFiles().first());
}

void MainWindow::about() {
  auto aboutMsg = tr("The <b>PowerLab</b> is to help modeling electronic schemes "
                     "by providing simple interface and convinient tools to analyze model results "
                     "as transient and spectral analyzis");

  QMessageBox::about(this, tr("About PowerLab"), aboutMsg);
}

void MainWindow::documentWasModified() {
  setWindowModified(false);
}

void MainWindow::addDefaultModelDesignWidget() {
  QWidget* widget = new QWidget(this);
  createDockWindow(widget, WidgetType::MODEL_DESIGN);
}

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

  menuBar()->addSeparator();

  const QIcon addIcon = QIcon::fromTheme("edit-add", QIcon(":/images/add.png"));
  m_addGraphAction = new QAction(addIcon, tr("&Add"), this);
  m_addGraphAction->setShortcuts(QKeySequence::New);
  m_addGraphAction->setStatusTip(tr("Select signals to plot new graph"));
  editToolBar->addAction(m_addGraphAction);
  m_addGraphAction->setDisabled(true);
  connect(m_addGraphAction, &QAction::triggered, this, [this](){
    if(this->m_modelResult) {
      this->showMetaData(true, "");
    }
  });

  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  QAction* aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
  aboutAct->setStatusTip(tr("Show the application's About box"));

//  QAction* aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
//  aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

  cutAct->setEnabled(false);
  copyAct->setEnabled(false);
//    connect(textEdit, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
//    connect(textEdit, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
}

Qt::DockWidgetArea MainWindow::getDockAreaForWidgetType(WidgetType type) const {
  Qt::DockWidgetArea area = Qt::NoDockWidgetArea;
  switch(type) {
    case WidgetType::MODEL_DESIGN: area = Qt::TopDockWidgetArea; break;
    case WidgetType::MODEL_RESULT: area = Qt::BottomDockWidgetArea; break;
    case WidgetType::PARAMS: area = Qt::LeftDockWidgetArea; break;
  }

  return area;
}

void MainWindow::createDockWindow(QWidget* widget, WidgetType type, const QString& windowTitle) {
  auto dockPosition = getDockAreaForWidgetType(type);

  QDockWidget *dock = new QDockWidget(windowTitle, this);
  dock->setAllowedAreas(dockPosition);
  dock->setWidget(widget);

  bool tabified = false;
  for(auto d : m_docksList) {
    if(d->allowedAreas() & dockPosition) {
      tabifyDockWidget(d, dock);
      tabified = true;
      break;
    }
  }

  if(!tabified) {
    addDockWidget(dockPosition, dock);
  }

  m_docksList.push_back(dock);

//    m_viewMenu->addAction(dock->toggleViewAction());
}

void MainWindow::addModelResultWidget(QWidget* widget, const QString& title) {
  createDockWindow(widget, WidgetType::MODEL_RESULT, title);
}

void MainWindow::createStatusBar() {
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings() {
  QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
  const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
  if(geometry.isEmpty()) {
    const QRect availableGeometry = screen()->availableGeometry();
    resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
    move((availableGeometry.width() - width()) / 2,
         (availableGeometry.height() - height()) / 2);
  } else {
    restoreGeometry(geometry);
  }
}

void MainWindow::writeSettings() {
  QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
  settings.setValue("geometry", saveGeometry());
}

bool MainWindow::maybeSave() {
  auto msgText = tr("The document has been modified.\n"
                    "Do you want to save your changes?");
  auto msgBoxes = QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel;
  const QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("PowerLab"), msgText, msgBoxes);

  switch (ret) {
    case QMessageBox::Save:
      return save();
    case QMessageBox::Cancel:
      return false;
    default:
      break;
  }

  return true;
}

bool MainWindow::saveFile(const QString &fileName) {
  QString errorMessage;

  QGuiApplication::setOverrideCursor(Qt::WaitCursor);
//    QSaveFile file(fileName);
//    if (file.open(QFile::WriteOnly | QFile::Text)) {
//        QTextStream out(&file);
//        out << textEdit->toPlainText();
//        if (!file.commit()) {
//            errorMessage = tr("Cannot write file %1:\n%2.")
//                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
//        }
//    } else {
//        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
//                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
//    }
//    QGuiApplication::restoreOverrideCursor();

//    if (!errorMessage.isEmpty()) {
//        QMessageBox::warning(this, tr("Application"), errorMessage);
//        return false;
//    }

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("File saved"), 2000);
  return true;
}

void MainWindow::setCurrentFile(const QString &fileName) {
  m_currentFile = fileName;
  setWindowModified(false);

  QString shownName = m_currentFile;
  if(m_currentFile.isEmpty()) {
    shownName = "untitled.dat";
  }
  setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName) {
  return QFileInfo(fullFileName).fileName();
}

void MainWindow::commitData(QSessionManager &manager) {
  if(manager.allowsInteraction()) {
    if(!maybeSave()) {
      manager.cancel();
    }
  } else {
    save();
  }
}

void MainWindow::showMetaData(bool parsingResult, const std::string& msg) {
  if(parsingResult) {
    MetaDataWindow* window = new MetaDataWindow(this);
    connect(window, &MetaDataWindow::accepted, this, &MainWindow::drawGraph);
    m_graphData = window->loadModelResults(*m_modelResult);
    window->show();

    m_addGraphAction->setEnabled(true);
  } else {
    m_metaDataWindow->setIcon(QMessageBox::Warning);
    m_metaDataWindow->setWindowTitle("Error");
    m_metaDataWindow->setText(QString::fromStdString(msg));
    m_metaDataWindow->setDefaultButton(QMessageBox::Close);
  }
}

void MainWindow::openModelResults(const QString& filename) {
  m_modelResult = std::make_unique<Model::ModelResult>();

  if(m_metaDataWindow && m_modelResult) {
    m_metaDataLoadedCB = [this](bool parsingResult, const std::string& msg) {
      this->showMetaData(parsingResult, msg);
    };
    m_modelResult->setupMetaDataLoadCB(m_metaDataLoadedCB);
  }

  if(m_modelResult) {
    m_modelResult->openFile(filename.toStdString());
  }
}

void MainWindow::drawGraph() {
  m_graphWidget = new GraphWidget();

  addModelResultWidget(m_graphWidget,
                       QString::fromStdString(m_modelResult->getModelTitle()));

  std::vector<std::string> signalNames;
  if(m_graphData) {
    int rows = m_graphData->rowCount();
    for(int i = 0; i < rows; i++) {
      auto idx = m_graphData->index(i, 0);
      auto item = m_graphData->data(idx);
      if(item.isValid()) {
        signalNames.push_back(item.toString().toStdString());
      }
    }
  }

  if(signalNames.size() < 1) {
    Logger::log(GuiMessage::ERROR_NO_SELECTED_SIGNALS_TO_PLOT);
    return;
  }

//  std::string refSigName = signalNames.front();
  std::string refSigName = m_modelResult->getReferenceSignalName();
  auto unit = m_modelResult->getSignalUnitsSISymbol(refSigName);
  auto&& signalData = m_modelResult->getSignalDataPoints(refSigName);
  m_graphWidget->addHorizontalScaleData(refSigName, unit, std::move(signalData));

  for(auto& item : signalNames) {
    unit = m_modelResult->getSignalUnitsSISymbol(item);
    signalData = m_modelResult->getSignalDataPoints(item);
    m_graphWidget->addGraphData(item, unit, std::move(signalData));
  }

  m_graphWidget->plot();
}

} // namespace Gui
