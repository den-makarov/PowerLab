#include <QAction>
#include <QAbstractItemModel>
#include <QMessageBox>

#include "logger.h"
#include "modelresult/modelresultvalidator.h"
#include "modelresult/modelresultmeta.h"
#include "dialogs/metadatawindow.h"
#include "graphs/graphwidget.h"
#include "mainwindow/mainwindow.h"

namespace PowerLab {
namespace Gui {

void MainWindow::resetGraphWidgetToDefaultView() {
  for(auto widget : m_graphWidgetSet) {
    if(widget->isActiveWindow()) {
      widget->resetDefaultView();
    }
  }
}

void MainWindow::setGraphWidgetZoom(bool enable) {
  for(auto widget : m_graphWidgetSet) {
    widget->setZoomEnabled(enable);
  }
}

void MainWindow::addModelResultWidget(QWidget* widget, const QString& title) {
  createDockWindow(widget, WidgetType::MODEL_RESULT, title);
}

void MainWindow::showMetaData(bool parsingResult, const std::string& msg) {
  if(parsingResult) {
    MetaDataWindow* window = new MetaDataWindow(this);
    connect(window, &MetaDataWindow::accepted, this, &MainWindow::drawGraph);
    m_graphData = window->loadModelResults(*m_modelResult);
    window->show();

    m_addGraphAction->setEnabled(true);
  } else {
    auto errorMessage = new QMessageBox(this);

    errorMessage->setIcon(QMessageBox::Critical);
    errorMessage->setWindowTitle("Error");
    errorMessage->setText(QString::fromStdString(msg));
    errorMessage->setDefaultButton(QMessageBox::Close);
  }
}

void MainWindow::openModelResults(const QString& filename) {
  m_modelResult = std::make_unique<Model::ModelResult>();

  if(m_modelResult) {
    m_metaDataLoadedCB = [this](bool parsingResult, const std::string& msg) {
      this->showMetaData(parsingResult, msg);
    };
    m_modelResult->setupMetaDataLoadCB(m_metaDataLoadedCB);
  }

  if(m_modelResult) {
    m_modelResult->openFile(filename.toStdString());
  }
}

void MainWindow::drawGraph() {
  GraphWidget* graphWidget = new GraphWidget();
  m_graphWidgetSet.push_back(graphWidget);

  addModelResultWidget(graphWidget,
                       QString::fromStdString(m_modelResult->getModelTitle()));

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

//  std::string refSigName = signalNames.front();
  std::string refSigName = m_modelResult->getReferenceSignalName();
  auto unit = m_modelResult->getSignalUnitsSISymbol(refSigName);
  auto&& signalData = m_modelResult->getSignalDataPoints(refSigName);
  graphWidget->addHorizontalScaleData(refSigName, unit, std::move(signalData));

  for(auto& item : signalNames) {
    unit = m_modelResult->getSignalUnitsSISymbol(item);
    signalData = m_modelResult->getSignalDataPoints(item);
    graphWidget->addGraphData(item, unit, std::move(signalData));
  }

  graphWidget->plot();
}

} // namespace Gui
} // namespace PowerLab
