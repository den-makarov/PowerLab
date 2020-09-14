#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>

#include "logger.h"
#include "mainwindow.h"
#include "modelresult.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{
  this->setMinimumWidth(MIN_WINDOW_WIDTH);
  this->setMinimumHeight(MIN_WINDOW_HEIGHT);

  ModelResult* result = new ModelResult(this);
  QPushButton* openFile = new QPushButton(this);

  if(openFile) {
    openFile->setText("&Open");
    openFile->show();
    connect(openFile, &QPushButton::pressed, result, &ModelResult::openFile);
  }
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
}
