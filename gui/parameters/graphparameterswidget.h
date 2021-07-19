#ifndef GRAPHPARAMETERSWIDGET_H
#define GRAPHPARAMETERSWIDGET_H

#include "parameterswidget.h"

class QComboBox;
class QGridLayout;
class QPushButton;
class QCheckBox;
class QSpinBox;
class QDoubleSpinBox;

namespace PowerLab {
namespace Gui {

class GraphParametersModel;
class GraphWidget;

class GraphParametersWidget : public ParametersWidget {
  Q_OBJECT
public:
  GraphParametersWidget(QWidget *parent = nullptr, std::vector<GraphWidget*> graphs = {});
  void updateGraphList(std::vector<GraphWidget*> graphs);

signals:
  void graphListUpdated();

private:
  enum class ColorControl {
    BACKGROUND_COLOR,
    GRID_LINES_COLOR,
    GRAPH_DATA_LINE_COLOR
  };

private slots:
  void graphSelectorChanged(int idx);
  void autoGridChanged(int state);
  void colorControlRequested(ColorControl control);

private:
  void updateView();
  void updateGraphParametersView(GraphWidget* graph);
  void updateGridColors(const GraphParametersModel& model);
  void updateGridLines(const GraphParametersModel& model);
  void updateGraphData(const GraphParametersModel& model);

  void setGraphParametersVisible(bool visible);

  void createGraphSelector();
  void createPlotColorControls();
  void createPlotGridControls();
  void createGraphDataControls();
  void addHorizontalSeparator(int rowIndex);
  void addLabel(const QString& text, int row, int column);
  void setManualGridControlsEnabled(bool enabled);

  int findFocusedGraphIdx() const;
  GraphWidget* getCurrentGraph() const;
  void setDoubleSpinBoxValue(QDoubleSpinBox& box, double number);

  std::vector<GraphWidget*> m_graphs;
  QGridLayout* m_grid = nullptr;
  QComboBox* m_graphSelector = nullptr;
  QPushButton* m_bgColorButton = nullptr;
  QPushButton* m_gridColors = nullptr;
  QCheckBox* m_isAutoGrid = nullptr;
  QSpinBox* m_hLines = nullptr;
  QSpinBox* m_vLines = nullptr;
  QDoubleSpinBox* m_hMin = nullptr;
  QDoubleSpinBox* m_hMax = nullptr;
  QDoubleSpinBox* m_vMin = nullptr;
  QDoubleSpinBox* m_vMax = nullptr;

  std::vector<QWidget*> m_layoutElements;
  std::vector<QWidget*> m_manualGridControls;

  constexpr static int NO_GRAPH_FOCUSED = -1;
};

} // namespace Gui
} // namespace PowerLab

#endif // GRAPHPARAMETERSWIDGET_H
