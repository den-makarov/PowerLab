#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QGridLayout>
#include <QKeySequence>
#include <QStatusBar>
#include <QToolBar>
#include <QThread>
#include <QTimer>

#include "logger.h"
#include "mainwindow.h"
#include "modelresult.h"
#include "metadatawindow.h"

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

  QMenuBar* menuBar = new QMenuBar(this);
  QMenu* menuFile = new QMenu("&File", this);
  QMenu* menuEdit = new QMenu("&Edit", this);
  QMenu* menuSelection = new QMenu("&Selection", this);
  QMenu* menuTools = new QMenu("&Tools", this);
  QMenu* menuHelp = new QMenu("&Help", this);

  QKeySequence scKeyOpen(QKeySequence::Open);
  menuBar->addMenu(menuFile);
  menuBar->addMenu(menuEdit);
  menuBar->addMenu(menuSelection);
  menuBar->addMenu(menuTools);
  menuBar->addMenu(menuHelp);

  QToolBar* toolBar = new QToolBar("Data", this);
  auto openAction = toolBar->addAction("Open", result, &ModelResult::openFile);

  QIcon viewIcon("images/icon.png");
  toolBar->addAction(viewIcon, "View", result, &ModelResult::openFile);

  m_metaDataWindow = new QMessageBox(this);
  QStatusBar* m_statusBar = new QStatusBar(this);
  menuFile->addAction("&Open", result, &ModelResult::openFile, scKeyOpen);

  auto openFileActionHovered = [m_statusBar, this](){
    auto mes = m_statusBar->currentMessage();
    m_statusBar->showMessage("Open a file with model results");
    QTimer::singleShot(2000, [m_statusBar, this](){
      this->showReadyStatus(m_statusBar);
    });
  };

  connect(openAction, &QAction::hovered, this, openFileActionHovered);

  QGridLayout *layout = new QGridLayout(this);
  layout->setMenuBar(menuBar);
  layout->addWidget(toolBar, 0, 0, Qt::AlignTop);
  layout->addWidget(m_statusBar, 1, 0, Qt::AlignBottom);
  layout->setSpacing(0);
  auto margins = layout->contentsMargins();
  margins.setTop(0);
  margins.setLeft(0);
  margins.setBottom(0);
  layout->setContentsMargins(margins);

  m_statusBar->showMessage("Ready");

  if(m_metaDataWindow) {
    connect(result, &ModelResult::metaDataLoaded, this, &MainWindow::showMetaData);
  }
}

/**
 * @brief MainWindow::showReadyStatus
 * @param status
 */
void MainWindow::showReadyStatus(QStatusBar* status) {
  if(status) {
    status->showMessage("Ready");
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
    MetaDataWindow* window = new MetaDataWindow(this);
    window->loadModelResults(data);
    window->show();
  } else {
    m_metaDataWindow->setIcon(QMessageBox::Warning);
    m_metaDataWindow->setWindowTitle("Error");
    m_metaDataWindow->setText(msg);
    m_metaDataWindow->setDefaultButton(QMessageBox::Close);
  }
}
