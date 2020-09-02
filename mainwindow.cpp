#include <QDebug>
#include <QPushButton>

#include "mainwindow.h"
#include "modelresult.h"

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{
  this->setMinimumWidth(400);
  this->setMinimumHeight(200);

  ModelResult* result = new ModelResult(0, 0, this);
  QPushButton* openFile = new QPushButton(this);
  if(openFile) {
    openFile->setText("&Open");
    openFile->show();
    connect(openFile, &QPushButton::pressed, this, [=](){
      openFile->setText("&Close");
      qDebug() << "[" << this->metaObject()->className() << "]"
               << "Variables in model results" << result->getVariablesNumber();
      qDebug() << "[" << this->metaObject()->className() << "]"
               << "Points in model results" << result->getPointsNumber();
    });
  }
}

MainWindow::~MainWindow()
{
}

