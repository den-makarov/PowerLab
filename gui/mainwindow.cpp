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
#include <QAbstractItemModel>

#include "backend/logger/logger.h"
#include "backend/modelresult/modelresult.h"
#include "gui/dialogs/metadatawindow.h"
#include "gui/graphs/graphprocessor.h"
#include "mainwindow.h"
/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{ 
  setWindowState(Qt::WindowState::WindowMaximized);
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

  m_metaDataWindow = new QMessageBox(this);
  menuFile->addAction("&Open", result, &ModelResult::openFile, scKeyOpen);

  QGridLayout *layout = new QGridLayout(this);
  setLayout(layout);
  layout->setMenuBar(menuBar);

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
    MetaDataWindow* window = new MetaDataWindow(this);
    connect(window, &MetaDataWindow::accepted, this, &MainWindow::DrawGraph);
    graph_data = window->loadModelResults(data);
    window->show();
  } else {
    m_metaDataWindow->setIcon(QMessageBox::Warning);
    m_metaDataWindow->setWindowTitle("Error");
    m_metaDataWindow->setText(msg);
    m_metaDataWindow->setDefaultButton(QMessageBox::Close);
  }
}

void MainWindow::DrawGraph() {
  if(layout()) {
    if(w) {
      layout()->removeWidget(w);
//      delete w;
    }
    graph = new GraphProcessor();
    w = new Widget(graph, this);
    layout()->addWidget(w);
  }

  QStringList signal_names;
  if(graph_data) {
    int rows = graph_data->rowCount();
    for(int i = 0; i < rows; i++) {
      auto idx = graph_data->index(i, 0);
      auto item = graph_data->data(idx);
      if(item.isValid()) {
        signal_names << item.toString();
      }
    }
  }

  w->setNames(signal_names);
  w->plot();
}
