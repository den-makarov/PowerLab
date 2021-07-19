#ifndef GRAPHPARAMETERSWIDGET_H
#define GRAPHPARAMETERSWIDGET_H

#include "parameterswidget.h"

class QComboBox;
class QGridLayout;
class QPushButton;
class QCheckBox;

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
  void updateGraphParametersView(GraphWidget* graph);
  void updateView();

  void setGraphParametersVisible(bool visible);

  void createGraphSelector();
  void createPlotColorControls();
  void createPlotGridControls();
  void createGraphDataControls();

  int findFocusedGraphIdx() const;

  std::vector<GraphWidget*> m_graphs;
  QGridLayout* m_grid = nullptr;
  QComboBox* m_graphSelector = nullptr;
  QPushButton* m_bgColorButton = nullptr;
  QPushButton* m_gridColors = nullptr;
  QCheckBox* m_isAutoGrid = nullptr;

  constexpr static int NO_GRAPH_FOCUSED = -1;
};

} // namespace Gui
} // namespace PowerLab

#endif // GRAPHPARAMETERSWIDGET_H
