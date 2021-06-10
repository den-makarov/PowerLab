#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>

#include "modelresult/modelresultmeta.h"
#include "modelresult/modelresult.h"

class QMessageBox;
class GraphProcessor;
class QAbstractItemModel;
class Widget;

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
  Model::ModelResult::MetaDataLoadCB metaDataLoaded;
  Model::ModelResult* result = nullptr;
  GraphProcessor* graph = nullptr;
  QMessageBox* m_metaDataWindow = nullptr;
  QAbstractItemModel* graph_data = nullptr;
  int m_graphColumns = 1;
  Widget* w = nullptr;

  constexpr static size_t MIN_WINDOW_WIDTH = 400;
  constexpr static size_t MIN_WINDOW_HEIGHT = 200;
};

} // namespace Gui
#endif // MAINWINDOW_H
