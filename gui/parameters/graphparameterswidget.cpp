#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>

#include "graphparameterswidget.h"
#include "graphs/graphwidget.h"
#include "graphs/graphparametersmodel.h"
#include "logger.h"

namespace PowerLab {
namespace Gui {

GraphParametersWidget::GraphParametersWidget(QWidget *parent, std::vector<GraphWidget*> graphs)
  : ParametersWidget(parent)
  , m_graphs(graphs)
{
  m_grid = new QGridLayout;
  m_grid->setAlignment(Qt::AlignTop);
  setLayout(m_grid);

  createGraphSelector();
  createPlotColorControls();
  createPlotGridControls();
  createGraphDataControls();

  updateView();
}

void GraphParametersWidget::updateGraphList(std::vector<GraphWidget*> graphs) {
  m_graphs = graphs;
  updateView();
  emit graphListUpdated();
}

void GraphParametersWidget::createGraphSelector() {
  QLabel* graphSelectorLabel = new QLabel(tr("Graph selector"));

  m_graphSelector = new QComboBox;
  for(size_t idx = 0; idx < m_graphs.size(); idx++) {
    auto graph = m_graphs[idx];
    m_graphSelector->addItem(graph->objectName(), QVariant::fromValue(idx));
  }

  connect(m_graphSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){
    GraphWidget* graph = nullptr;
    size_t idx = static_cast<size_t>(index);

    if(idx < this->m_graphs.size()) {
      graph = this->m_graphs.at(idx);
    }

    this->updateGraphParametersView(graph);
  });

  m_grid->addWidget(graphSelectorLabel, 0, 0);
  m_grid->addWidget(m_graphSelector, 1, 0);
}

void GraphParametersWidget::createPlotColorControls() {
  m_bgColorButton = new QPushButton(tr("Background color"));
  connect(m_bgColorButton, &QPushButton::clicked, [this](bool /*Not interested*/){
    const QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
//    auto color = this->setColor();
    if(color.isValid()) {
      this->m_bgColorButton->setPalette(QPalette(color));
      this->m_bgColorButton->setAutoFillBackground(true);
      auto graphIdx = this->m_graphSelector->currentData();
      if(graphIdx.isValid()) {
        GraphParametersModel model(*this->m_graphs[graphIdx.toUInt()]);
        model.setBackgroundColor(color);
        this->m_graphs[graphIdx.toUInt()]->repaint();
      }
    }
  });

  m_grid->addWidget(m_bgColorButton, 3, 0);

  m_gridColors = new QPushButton(tr("Grid color"));
  connect(m_gridColors, &QPushButton::clicked, [this](bool /*Not interested*/){
    const QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
//    auto color = this->setColor();
    if(color.isValid()) {
      this->m_gridColors->setPalette(QPalette(color));
      this->m_gridColors->setAutoFillBackground(true);
      auto graphIdx = this->m_graphSelector->currentData();
      if(graphIdx.isValid()) {
        GraphParametersModel model(*this->m_graphs[graphIdx.toUInt()]);
        model.setGridLinesColor(color);
        this->m_graphs[graphIdx.toUInt()]->repaint();
      }
    }
  });

  m_grid->addWidget(m_gridColors, 3, 1);
}

void GraphParametersWidget::createPlotGridControls() {
  m_isAutoGrid = new QCheckBox("Auto grid");
  m_isAutoGrid->setChecked(true);

  m_grid->addWidget(m_isAutoGrid, 5, 0);
}

void GraphParametersWidget::createGraphDataControls() {

}

void GraphParametersWidget::updateView() {
  m_graphSelector->clear();
  for(size_t idx = 0; idx < m_graphs.size(); idx++) {
    auto graph = m_graphs[idx];
    m_graphSelector->addItem(graph->objectName(), QVariant::fromValue(idx));
  }

  auto focusedGraphIdx = findFocusedGraphIdx();
  if(focusedGraphIdx != NO_GRAPH_FOCUSED) {
    m_graphSelector->setCurrentIndex(focusedGraphIdx);
    updateGraphParametersView(m_graphs[static_cast<size_t>(focusedGraphIdx)]);
    setGraphParametersVisible(true);
  } else {
    setGraphParametersVisible(false);
  }
}

void GraphParametersWidget::setGraphParametersVisible(bool visible) {
  m_bgColorButton->setVisible(visible);
  m_gridColors->setVisible(visible);
  m_isAutoGrid->setVisible(visible);
}

int GraphParametersWidget::findFocusedGraphIdx() const {
  int focusedGraphIdx = NO_GRAPH_FOCUSED;

  if(m_graphs.size() != 0) {
    focusedGraphIdx = 0;
    auto focusedWidget = qApp->focusWidget();

    for(auto graph : m_graphs) {
      if(graph == focusedWidget) {
        break;
      }
      focusedGraphIdx++;
    }

    if(static_cast<size_t>(focusedGraphIdx) >= m_graphs.size()) {
      focusedGraphIdx = 0;
    }
  }

  return focusedGraphIdx;
}

void GraphParametersWidget::updateGraphParametersView(GraphWidget* graph) {
  if(!graph) {
    setGraphParametersVisible(false);
    return;
  }

  GraphParametersModel model(*graph);

  m_bgColorButton->setPalette(model.getBackgroundColor());
//  bgColorButton->setFlat(true);
  m_bgColorButton->setAutoFillBackground(true);

  m_gridColors->setPalette((model.getGridLinesColor()));
  m_gridColors->setAutoFillBackground(true);

  m_isAutoGrid->setChecked(model.isAutoGrid());
}

} // namespace Gui
} // namespace PowerLab
