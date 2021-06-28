#include <QSettings>
#include <QMessageBox>
#include <QStatusBar>
#include <QFileDialog>
#include <QFile>
#include <QtWidgets>

#include "mainwindow/mainwindow.h"

namespace Gui {

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
  auto dialogTitle = tr("Open model design file or model simulation result file");
  auto dialogFilter = tr("Model design or results (*.pmd *.pmr)");
  QString filename = QFileDialog::getOpenFileName(this, dialogTitle, "", dialogFilter);

  if(!filename.isEmpty()) {
    openModelResults(filename);
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
    shownName = "untitled.plm";
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

} // namespace Gui
