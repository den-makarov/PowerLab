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
class QTabWidget;
class QMessageBox;
class QAbstractItemModel;
class QPlainTextEdit;
class QSessionManager;
QT_END_NAMESPACE

namespace Gui {

class GraphWidget;

class MainWindow : public QMainWindow {
Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);

  void loadFile(const QString &fileName);

  void openModelResults(const QString& filename);
protected:
  void closeEvent(QCloseEvent *event) override;

private slots:
  void drawGraph();
  void newFile();
  void open();
  bool save();
  bool saveAs();
  void about();
  void documentWasModified();
  void commitData(QSessionManager &);

private:
  enum class WidgetType {
    MODEL_DESIGN,
    MODEL_RESULT,
    PARAMETERS,
    LIBRARY
  };

  void createActions();
  void addDefaultModelDesignWidget();
  void showLibrary();
  void showParameters();
  void createDockWindow(QWidget* widget, WidgetType pos, const QString& windowTitle = "Empty");
  Qt::DockWidgetArea getDockAreaForWidgetType(WidgetType type) const;
  void addModelResultWidget(QWidget* widget, const QString& title = "Empty");
  void createStatusBar();
  void readSettings();
  void writeSettings();
  bool maybeSave();
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

  void showMetaData(bool parsingResult, const std::string& msg = "");

  std::unique_ptr<Model::ModelResult> m_modelResult;

  QString m_currentFile;
  GraphWidget* m_graphWidget = nullptr;
  QAbstractItemModel* m_graphData = nullptr;
  QMenu* m_viewMenu;

  Model::ModelResult::MetaDataLoadCB m_metaDataLoadedCB;

  QAction* m_addGraphAction = nullptr;
  std::vector<QDockWidget*> m_docksList;

  constexpr static size_t MIN_WINDOW_WIDTH = 400;
  constexpr static size_t MIN_WINDOW_HEIGHT = 200;
};

} // namespace Gui
#endif // MAINWINDOW_H
