#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>

#include "modelresult/modelresultmeta.h"
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

  void showMetaData(const Model::ModelResultMeta::Data*, const std::string& msg = "");
  void openModelResults();

private slots:
  void DrawGraph();

private:
  Model::ModelResult::MetaDataLoadCB m_metaDataLoadedCB;
  Model::ModelResult* m_modelResult = nullptr;
  GraphProcessor* m_graphProcessor = nullptr;
  QMessageBox* m_metaDataWindow = nullptr;
  QAbstractItemModel* m_graphData = nullptr;
  GraphWidget* m_graphWidget = nullptr;

  int m_graphColumns = 1;
  constexpr static size_t MIN_WINDOW_WIDTH = 400;
  constexpr static size_t MIN_WINDOW_HEIGHT = 200;
};

} // namespace Gui
#endif // MAINWINDOW_H
