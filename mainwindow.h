#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>

#include "modelresultmeta.h"

class QMessageBox;

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void showMetaData(const ModelResultMeta::Data*, QString msg = "");

private:
  QMessageBox* m_metaDataWindow = nullptr;
  int m_graphColumns = 1;

  constexpr static size_t MIN_WINDOW_WIDTH = 400;
  constexpr static size_t MIN_WINDOW_HEIGHT = 200;
};
#endif // MAINWINDOW_H
