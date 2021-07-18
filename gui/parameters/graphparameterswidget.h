#ifndef GRAPHPARAMETERSWIDGET_H
#define GRAPHPARAMETERSWIDGET_H

#include "parameterswidget.h"

class QComboBox;
class QGridLayout;

namespace PowerLab {
namespace Gui {

class GraphWidget;

class GraphParametersWidget : public ParametersWidget {
  Q_OBJECT
public:
  GraphParametersWidget(QWidget *parent = nullptr, std::vector<GraphWidget*> graphs = {});
  void updateGraphList(std::vector<GraphWidget*> graphs);

signals:
  void graphListUpdated();

private:
  void updateGraphParamsView(GraphWidget* graph);
  void updateView();
  void createGraphListSelector();
  int findFocusedGraphIdx() const;

  std::vector<GraphWidget*> m_graphs;
  QComboBox* m_graphWidgetList = nullptr;
  QGridLayout* m_grid;

  constexpr static int NO_GRAPH_FOCUSED = -1;
};

} // namespace Gui
} // namespace PowerLab

#endif // GRAPHPARAMETERSWIDGET_H
