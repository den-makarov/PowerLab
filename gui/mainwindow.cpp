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
#include "modelresult/modelresultvalidator.h"
#include "modelresult/modelresultmeta.h"
#include "dialogs/metadatawindow.h"
#include "graphs/graphprocessor.h"
#include "mainwindow.h"

namespace Gui {

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{ 
  setWindowState(Qt::WindowState::WindowMaximized);
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

  QGridLayout* layout = new QGridLayout(this);
  setLayout(layout);
  layout->setMenuBar(menuBar);

  m_metaDataWindow = new QMessageBox(this);
}

MainWindow::~MainWindow() {}

void MainWindow::showMetaData(bool parsingResult, const std::string& msg) {
  if(parsingResult) {
    MetaDataWindow* window = new MetaDataWindow(this);
    connect(window, &MetaDataWindow::accepted, this, &MainWindow::DrawGraph);
    m_graphData = window->loadModelResults(*m_modelResult);
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

  m_modelResult = std::make_unique<Model::ModelResult>();

  if(m_metaDataWindow && m_modelResult) {
    m_metaDataLoadedCB = [this](bool parsingResult, const std::string& msg) {
      this->showMetaData(parsingResult, msg);
    };
    m_modelResult->setupMetaDataLoadCB(m_metaDataLoadedCB);
  }

  if(m_modelResult) {
    m_modelResult->openFile(filename.toStdString());
  }
}

void MainWindow::DrawGraph() {
  if(layout()) {
    if(m_graphWidget) {
      layout()->removeWidget(m_graphWidget);
      delete m_graphWidget;
    }

    m_graphWidget = new GraphWidget(this);
    layout()->addWidget(m_graphWidget);
  }

  std::vector<std::string> signalNames;
  if(m_graphData) {
    int rows = m_graphData->rowCount();
    for(int i = 0; i < rows; i++) {
      auto idx = m_graphData->index(i, 0);
      auto item = m_graphData->data(idx);
      if(item.isValid()) {
        signalNames.push_back(item.toString().toStdString());
      }
    }
  }

  if(signalNames.size() < 1) {
    Logger::log(GuiMessage::ERROR_NO_SELECTED_SIGNALS_TO_PLOT);
    return;
  }

  std::string refSigName = m_modelResult->getReferenceSignalName();
  m_graphWidget->addHorizontalScaleData(refSigName,
                                        m_modelResult->getSignalUnitsSISymbol(refSigName),
                                        m_modelResult->getSignalDataPoints(refSigName));

  for(auto& item : signalNames) {
    m_graphWidget->addGraphData(item,
                                m_modelResult->getSignalUnitsSISymbol(item),
                                m_modelResult->getSignalDataPoints(item));
  }

  m_graphWidget->plot();
}

} // namespace Gui
