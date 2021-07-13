#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>

#include "graphparameterswidget.h"
#include "graphs/graphwidget.h"

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
  emit graphListUpdated();
}

void GraphParametersWidget::updateView() {
  QGroupBox* graphWidgetsGroup = new QGroupBox(tr("Graph selector"));

  QVBoxLayout *graphWidgetLayout = new QVBoxLayout;
  QComboBox* graphWidgetList = new QComboBox;
  for(size_t idx = 0; idx < m_graphs.size(); idx++) {
    auto graph = m_graphs[idx];
    graphWidgetList->addItem(graph->objectName(), QVariant::fromValue(idx));
  }

  graphWidgetLayout->setAlignment(Qt::AlignTop);
  graphWidgetLayout->addWidget(graphWidgetList);
  graphWidgetsGroup->setLayout(graphWidgetLayout);

  QGridLayout* grid = new QGridLayout;
  grid->setAlignment(Qt::AlignTop);
  grid->addWidget(graphWidgetsGroup, 0, 0);

  setLayout(grid);

  auto focusedGraphIdx = findFocusedGraphIdx();
  if(focusedGraphIdx != NO_GRAPH_FOCUSED) {
    graphWidgetList->setCurrentIndex(focusedGraphIdx);
    updateGraphParamsView(m_graphs[static_cast<size_t>(focusedGraphIdx)]);
  }
}

int GraphParametersWidget::findFocusedGraphIdx() const {
  int focusedGraphIdx = NO_GRAPH_FOCUSED;

  if(m_graphs.size() != 0) {
    GraphWidget* selectedWidget = m_graphs.front();

    focusedGraphIdx = 0;
    auto focusedWidget = qApp->focusWidget();

    for(auto graph : m_graphs) {
      if(graph == focusedWidget) {
        selectedWidget = graph;
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
}

} // namespace Gui
} // namespace PowerLab
