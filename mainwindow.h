#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget
{
  Q_OBJECT
  constexpr static size_t MIN_WINDOW_WIDTH = 400;
  constexpr static size_t MIN_WINDOW_HEIGHT = 200;

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
};
#endif // MAINWINDOW_H
