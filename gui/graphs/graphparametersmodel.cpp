#include "graphparametersmodel.h"
#include "graphwidget.h"
#include "logger.h"

namespace PowerLab {
namespace Gui {

GraphParametersModel::GraphParametersModel(GraphWidget& graph)
  : m_graph(graph)
{
// EMMPTY
}

QRectF GraphParametersModel::getValueBounds() const {
  return m_graph.getPlot().getBoundsRect();
}

void GraphParametersModel::setValueBounds(QRectF bounds) {
  auto b = m_graph.getPlot().getBounds();
  b.yMin = bounds.bottom();
  b.yMax = bounds.top();
  b.xMin = bounds.left();
  b.xMax = bounds.right();
  m_graph.getPlot().setBounds(b);
}

bool GraphParametersModel::isAutoGrid() const {
  return m_graph.getPlot().isAutoGrid();
}

void GraphParametersModel::setAutoGrid(bool isAuto) {
  m_graph.getPlot().setAutoGrid(isAuto);
}

int GraphParametersModel::getGridLinesNumber(GridSide side) const {
  if(side == GridSide::X_SIDE) {
    return m_graph.getPlot().getMainGridLinesXNumber();
  } else {
    return m_graph.getPlot().getMainGridLinesYNumber();
  }
}

void GraphParametersModel::setGridLinesNumber(GridSide side, int number) {
  if(number < 0 || MAX_GRID_LINES_NUMBER < number) {
    Logger::log(GuiMessage::ERROR_INVALID_NUMBER_OF_GRID_LINES, number, 0, MAX_GRID_LINES_NUMBER);
    return;
  }

  if(side == GridSide::X_SIDE) {
    m_graph.getPlot().setMainGridLinesXNumber(number);
  } else {
    m_graph.getPlot().setMainGridLinesYNumber(number);
  }
}

QColor GraphParametersModel::getGridLinesColor() const {
  return m_graph.getPlot().getGridColor();
}

void GraphParametersModel::setGridLinesColor(QColor color) {
  m_graph.getPlot().setGridColor(color);
}

QColor GraphParametersModel::getBackgroundColor() const {
  return m_graph.getPlot().getBackground();
}

void GraphParametersModel::setBackgroundColor(QColor color) {
  m_graph.getPlot().setBackground(color);
}

double GraphParametersModel::getGridLinesOrigin(GridSide side) const {
  auto labels = m_graph.getPlot().getGridLabelsBounds();
  return (side == GridSide::X_SIDE) ? labels.xMin : labels.yMin;
}

void GraphParametersModel::setGridLinesOrigin(GridSide side, double origin) {
  auto labels = m_graph.getPlot().getGridLabelsBounds();
  (side == GridSide::X_SIDE) ? labels.xMin = origin : labels.yMin = origin;
  m_graph.getPlot().setGridLabelsBounds(labels);
}

double GraphParametersModel::getGridLinesEnd(GridSide side) const {
  auto labels = m_graph.getPlot().getGridLabelsBounds();
  return (side == GridSide::X_SIDE) ? labels.xMax : labels.yMax;
}

void GraphParametersModel::setGridLinesEnd(GridSide side, double end) {
  auto labels = m_graph.getPlot().getGridLabelsBounds();
  (side == GridSide::X_SIDE) ? labels.xMax = end : labels.yMax = end;
  m_graph.getPlot().setGridLabelsBounds(labels);
}

GraphParametersModel::GraphDataIdx GraphParametersModel::getGraphNumber() const {

}

QColor GraphParametersModel::getGraphColor(GraphDataIdx idx) const {

}

void GraphParametersModel::setGraphColor(GraphDataIdx idx, QColor) {

}

int GraphParametersModel::getLineWidth(GraphDataIdx idx) const {

}

void GraphParametersModel::setLineWidth(GraphDataIdx idx, int) {

}

std::string GraphParametersModel::getGraphName(GraphDataIdx idx) const {

}

void GraphParametersModel::setGraphName(GraphDataIdx idx, std::string) const {

}

std::string GraphParametersModel::getGraphUnits(GraphDataIdx idx) const {

}

void GraphParametersModel::setGraphUnits(GraphDataIdx idx, std::string) const {

}

std::string GraphParametersModel::getReferenceName(GraphDataIdx idx) const {

}

void GraphParametersModel::setReferencehName(GraphDataIdx idx, std::string) const {

}

std::string GraphParametersModel::getReferenceUnits(GraphDataIdx idx) const {

}

void GraphParametersModel::setReferenceUnits(GraphDataIdx idx, std::string) const {

}

} // namespace Gui
} // namespace PowerLab
