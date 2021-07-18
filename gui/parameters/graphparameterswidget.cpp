#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QCheckBox>

#include "graphparameterswidget.h"
#include "graphs/graphwidget.h"
#include "graphs/graphparametersmodel.h"

namespace PowerLab {
namespace Gui {

GraphParametersWidget::GraphParametersWidget(QWidget *parent, std::vector<GraphWidget*> graphs)
  : ParametersWidget(parent)
  , m_graphs(graphs)
{
  updateView();
}

void GraphParametersWidget::updateGraphList(std::vector<GraphWidget*> graphs) {
  m_graphs = graphs;
  updateView();
  emit graphListUpdated();
}

void GraphParametersWidget::createGraphListSelector() {
  QGroupBox* graphWidgetsGroup = new QGroupBox(tr("Graph selector"));

  QVBoxLayout* graphWidgetLayout = new QVBoxLayout;
  m_graphWidgetList = new QComboBox;
  for(size_t idx = 0; idx < m_graphs.size(); idx++) {
    auto graph = m_graphs[idx];
    m_graphWidgetList->addItem(graph->objectName(), QVariant::fromValue(idx));
  }

  graphWidgetLayout->setAlignment(Qt::AlignTop);
  graphWidgetLayout->addWidget(m_graphWidgetList);
  graphWidgetsGroup->setLayout(graphWidgetLayout);

  m_grid = new QGridLayout;
  m_grid->setAlignment(Qt::AlignTop);
  m_grid->addWidget(graphWidgetsGroup, 0, 0);

  setLayout(m_grid);
}

void GraphParametersWidget::updateView() {
  if(!m_graphWidgetList) {
    createGraphListSelector();
  } else {
    m_graphWidgetList->clear();
    for(size_t idx = 0; idx < m_graphs.size(); idx++) {
      auto graph = m_graphs[idx];
      m_graphWidgetList->addItem(graph->objectName(), QVariant::fromValue(idx));
    }
  }

  auto focusedGraphIdx = findFocusedGraphIdx();
  if(focusedGraphIdx != NO_GRAPH_FOCUSED) {
    m_graphWidgetList->setCurrentIndex(focusedGraphIdx);
    updateGraphParamsView(m_graphs[static_cast<size_t>(focusedGraphIdx)]);
  }
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

void GraphParametersWidget::updateGraphParamsView(GraphWidget* graph) {
  if(!graph) {
    return;
  }

  GraphParametersModel model(*graph);

  QGroupBox* graphGridSettingsGroup = new QGroupBox(tr("Grid settings"));
  QVBoxLayout* graphGridSettingsLayout = new QVBoxLayout;

  QCheckBox* isAutoGrid = new QCheckBox("Auto grid");
  isAutoGrid->setChecked(model.isAutoGrid());

  graphGridSettingsLayout->setAlignment(Qt::AlignTop);
  graphGridSettingsLayout->addWidget(isAutoGrid);

  graphGridSettingsGroup->setLayout(graphGridSettingsLayout);

  m_grid->addWidget(graphGridSettingsGroup, 1, 0);
}

} // namespace Gui
} // namespace PowerLab
