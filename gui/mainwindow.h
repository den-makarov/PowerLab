#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>

#include "backend/modelresult/modelresultmeta.h"
#include "backend/modelresult/modelresult.h"

class QMessageBox;
class GraphProcessor;
class QAbstractItemModel;
class Widget;

class MainWindow : public QWidget
{
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void showMetaData(const ModelResultMeta::Data*, const std::string& msg = "");
  void openModelResults();

private slots:
  void DrawGraph();

private:
  ModelResult::MetaDataLoadCB metaDataLoaded;
  ModelResult* result = nullptr;
  GraphProcessor* graph = nullptr;
  QMessageBox* m_metaDataWindow = nullptr;
  QAbstractItemModel* graph_data = nullptr;
  int m_graphColumns = 1;
  Widget* w = nullptr;

  constexpr static size_t MIN_WINDOW_WIDTH = 400;
  constexpr static size_t MIN_WINDOW_HEIGHT = 200;
};
#endif // MAINWINDOW_H
