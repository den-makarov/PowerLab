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

#include "logger.h"
#include "modelresult/modelresult.h"
#include "dialogs/metadatawindow.h"
#include "graphs/graphprocessor.h"
#include "mainwindow.h"

namespace Gui {

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{ 
  setWindowState(Qt::WindowState::WindowMaximized);
  result = new Model::ModelResult();
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

  menuFile->addAction("&Open", this, &MainWindow::openModelResults, scKeyOpen);

  QGridLayout *layout = new QGridLayout(this);
  setLayout(layout);
  layout->setMenuBar(menuBar);

  m_metaDataWindow = new QMessageBox(this);
  if(m_metaDataWindow && result) {
    metaDataLoaded = [this](const Model::ModelResultMeta::Data* data, const std::string& msg){
      this->showMetaData(data, msg);
    };
    result->setupMetaDataLoadCB(metaDataLoaded);
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
void MainWindow::showMetaData(const Model::ModelResultMeta::Data* data, const std::string& msg) {
  if(data) {
    MetaDataWindow* window = new MetaDataWindow(this);
    connect(window, &MetaDataWindow::accepted, this, &MainWindow::DrawGraph);
    graph_data = window->loadModelResults(data);
    window->show();
  } else {
    m_metaDataWindow->setIcon(QMessageBox::Warning);
    m_metaDataWindow->setWindowTitle("Error");
    m_metaDataWindow->setText(QString::fromStdString(msg));
    m_metaDataWindow->setDefaultButton(QMessageBox::Close);
  }
}

void MainWindow::openModelResults() {
  QString filename = QFileDialog::getOpenFileName(nullptr,
                                                  tr("Open file with modeling results"),
                                                  "",
                                                  tr("Modeling result files (*.esk *.dat)"));
  if(result) {
    result->openFile(filename.toStdString());
  }
}

void MainWindow::DrawGraph() {
  if(layout()) {
    if(w) {
      layout()->removeWidget(w);
      delete w;
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

} // namespace Gui
