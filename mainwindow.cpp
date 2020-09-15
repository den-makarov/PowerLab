#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

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
  m_metaDataWindow = new QMessageBox(this);

  if(openFile) {
    openFile->setText("&Open");
    openFile->show();
    connect(openFile, &QPushButton::pressed, result, &ModelResult::openFile);
  }

  if(m_metaDataWindow) {
    connect(result, &ModelResult::metaDataLoaded, this, &MainWindow::showMetaData);
  }
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
}

/**
 * @brief MainWindow::ShowMetaData
 * @param msg
 */
void MainWindow::showMetaData(const ModelResultMeta::Data* data, QString msg) {
  if(data) {
    m_metaDataWindow->setText(data->title);
    m_metaDataWindow->setIcon(QMessageBox::Information);
    m_metaDataWindow->setWindowTitle("Info: " + msg);
    m_metaDataWindow->setDefaultButton(QMessageBox::Ok);
  } else {
    m_metaDataWindow->setIcon(QMessageBox::Warning);
    m_metaDataWindow->setWindowTitle("Error");
    m_metaDataWindow->setText(msg);
    m_metaDataWindow->setDefaultButton(QMessageBox::Close);
  }

  m_metaDataWindow->exec();
}
