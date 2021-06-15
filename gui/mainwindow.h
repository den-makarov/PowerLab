#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QWidget>
#include <QString>

#include "modelresult/modelresult.h"

class QMessageBox;
class QAbstractItemModel;
class GraphProcessor;
class GraphWidget;

namespace Gui {

class MainWindow : public QWidget
{
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void showMetaData(bool parsingResult, const std::string& msg = "");
  void openModelResults();

private slots:
  void DrawGraph();

private:
  std::unique_ptr<Model::ModelResult> m_modelResult;

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
