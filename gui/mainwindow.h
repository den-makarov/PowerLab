#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QString>
#include <QMainWindow>

#include "modelresult/modelresultvalidator.h"
#include "modelresult/modelresult.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMessageBox;
class QAbstractItemModel;
class QPlainTextEdit;
class QSessionManager;
QT_END_NAMESPACE

namespace Gui {

class GraphProcessor;
class GraphWidget;

class MainWindow : public QMainWindow {
Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);

  void loadFile(const QString &fileName);

  void showMetaData(bool parsingResult, const std::string& msg = "");
  void openModelResults(const QString& filename);

protected:
  void closeEvent(QCloseEvent *event) override;

private slots:
  void DrawGraph();
  void newFile();
  void open();
  bool save();
  bool saveAs();
  void about();
  void documentWasModified();
  void commitData(QSessionManager &);

private:
  void createActions();
  void createStatusBar();
  void readSettings();
  void writeSettings();
  bool maybeSave();
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

  std::unique_ptr<Model::ModelResult> m_modelResult;

  QString m_currentFile;
  GraphWidget* m_graphWidget = nullptr;
  QMessageBox* m_metaDataWindow = nullptr;
  QAbstractItemModel* m_graphData = nullptr;

  Model::ModelResult::MetaDataLoadCB m_metaDataLoadedCB;

  int m_graphColumns = 1;
  constexpr static size_t MIN_WINDOW_WIDTH = 400;
  constexpr static size_t MIN_WINDOW_HEIGHT = 200;
};

} // namespace Gui
#endif // MAINWINDOW_H
