#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>

#include "logger.h"
#include "mainwindow.h"
#include "modelresult.h"
#include "modelresultvalidator.h"
#include "modelresultmeta.h"

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{
  this->setMinimumWidth(MIN_WINDOW_WIDTH);
  this->setMinimumHeight(MIN_WINDOW_HEIGHT);

  ModelResult* result;
  QPushButton* openFile = new QPushButton(this);
  QString* filename = new QString();

  if(openFile) {
    openFile->setText("&Open");
    openFile->show();
    connect(openFile, &QPushButton::pressed, this, [filename, &result, this](){
      *filename = QFileDialog::getOpenFileName(nullptr,
                                              tr("Open file with modeling results"),
                                              "",
                                              tr("Modeling result files (*.esk *.o)"));
      if(filename->isEmpty()) {
        return;
      }

      ModelResultValidator* validator = new ModelResultValidator(*filename, this);
      auto meta = validator->validate();
      if(meta) {
        E_DEBUG(this) << "Meta data ready";
        result = new ModelResult(meta->getData().varCount, meta->getData().points, this);
      }
    });
  }
}

MainWindow::~MainWindow()
{
}

