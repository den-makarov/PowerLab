#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>

#include "mainwindow.h"
#include "modelresult.h"

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{
  this->setMinimumWidth(MIN_WINDOW_WIDTH);
  this->setMinimumHeight(MIN_WINDOW_HEIGHT);

  ModelResult* result = new ModelResult(0, 0, this);
  QPushButton* openFile = new QPushButton(this);
  QString filename;

  if(openFile) {
    openFile->setText("&Open");
    openFile->show();
    connect(openFile, &QPushButton::pressed, this, [&filename, &result](){
      filename = QFileDialog::getOpenFileName(nullptr,
                                              tr("Open file with modeling results"),
                                              "",
                                              tr("Modeling result files (*.esk *.dat)"));

    });
  }
}

MainWindow::~MainWindow()
{
}

