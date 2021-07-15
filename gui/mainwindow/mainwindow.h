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
class QAbstractItemModel;
class QPlainTextEdit;
class QSessionManager;
QT_END_NAMESPACE

namespace PowerLab {
namespace Gui {

class GraphWidget;
class GraphParametersWidget;

class MainWindow : public QMainWindow {
Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);

  void loadFile(const QString &fileName);
  void openModelResults(const QString& filename);
  void debugMsg(std::string str);

signals:
  void fileOpened(QString filename);
  void newGraphWidget(QWidget* widget);

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
  void createZoomActions();
  void createEditActions();
  void createFileActions();
  void createViewActions();
  void createHelpActions();
  void createGraphActions();
  void createStatusBar();

  void readSettings();
  void writeSettings();

  bool maybeSave();
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

  void showLibrary();
  void showParameters();
  void showMetaData(bool parsingResult, const std::string& msg = "");

  void createDockWindow(QWidget* widget, WidgetType pos, const QString& windowTitle = "Empty");
  Qt::DockWidgetArea getDockAreaForWidgetType(WidgetType type) const;

  void addModelResultWidget(QWidget* widget, const QString& title = "Empty");
  void addDefaultModelDesignWidget();

  enum class ZoomKind {
    ZOOM_IN,
    ZOOM_OUT,
    ZOOM_RESET
  };

  void zoomEnableHandler(bool enable);
  void zoomInHandler();
  void zoomOutHandler();
  void zoomResetHandler();

  void setGraphWidgetZoom(bool enable);
  void graphWidgetZoom(ZoomKind zoom);

  std::vector<GraphWidget*> m_graphWidgetSet;
  QAbstractItemModel* m_graphData = nullptr;
  std::unique_ptr<Model::ModelResult> m_modelResult;
  Model::ModelResult::MetaDataLoadCB m_metaDataLoadedCB;

  QMenu* m_viewMenu;
  QAction* m_addGraphAction = nullptr;

  QString m_currentFile;

  std::vector<QDockWidget*> m_docksList;

  GraphParametersWidget* m_graphParameters = nullptr;

  QPlainTextEdit* m_logOutput = nullptr;

  constexpr static size_t MIN_WINDOW_WIDTH = 400;
  constexpr static size_t MIN_WINDOW_HEIGHT = 200;
};

} // namespace Gui
} // namespace PowerLab

#endif // MAINWINDOW_H
