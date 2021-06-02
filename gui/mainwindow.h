#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>

#include "backend/modelresult/modelresultmeta.h"

class QMessageBox;
class GraphProcessor;
class QAbstractItemModel;
class Widget;

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void showMetaData(const ModelResultMeta::Data*, QString msg = "");

private slots:
  void DrawGraph();

private:
  GraphProcessor* graph = nullptr;
  QMessageBox* m_metaDataWindow = nullptr;
  QAbstractItemModel* graph_data = nullptr;
  int m_graphColumns = 1;
  Widget* w = nullptr;

  constexpr static size_t MIN_WINDOW_WIDTH = 400;
  constexpr static size_t MIN_WINDOW_HEIGHT = 200;
};
#endif // MAINWINDOW_H
