#ifndef GRAPHPARAMETERSMODEL_H
#define GRAPHPARAMETERSMODEL_H

#include <QObject>
#include <QRectF>
#include <QColor>

namespace PowerLab {
namespace Gui {

class GraphWidget;

class GraphParametersModel final {
//  Q_OBJECT
public:
  using GraphDataIdx = size_t;

  enum class GridSide {
    X_SIDE,
    Y_SIDE
  };

  explicit GraphParametersModel(GraphWidget& graph);

  QRectF getValueBounds() const;
  void setValueBounds(QRectF bounds);

  QColor getGridLinesColor() const;
  void setGridLinesColor(QColor color);

  QColor getBackgroundColor() const;
  void setBackgroundColor(QColor color);

  bool isAutoGrid() const;
  void setAutoGrid(bool isAuto);

  int getGridLinesNumber(GridSide side) const;
  void setGridLinesNumber(GridSide side, int number);

  double getGridLinesOrigin(GridSide side) const;
  void setGridLinesOrigin(GridSide side, double origin);
  double getGridLinesEnd(GridSide side) const;
  void setGridLinesEnd(GridSide side, double end);

  GraphDataIdx getGraphNumber() const;

  QColor getGraphColor(GraphDataIdx idx) const;
  void setGraphColor(GraphDataIdx idx, QColor color);

  int getLineWidth(GraphDataIdx idx) const;
  bool setLineWidth(GraphDataIdx idx, int);

  std::string getGraphName(GraphDataIdx idx) const;
  void setGraphName(GraphDataIdx idx, std::string name) const;

  std::string getGraphUnits(GraphDataIdx idx) const;
  void setGraphUnits(GraphDataIdx idx, std::string units) const;

  std::string getReferenceName() const;
  void setReferencehName(std::string name);

  std::string getReferenceUnits() const;
  void setReferenceUnits(std::string units);

private:
  GraphWidget& m_graph;

  constexpr static int MAX_GRAPH_LINE_WIDTH = 10;
  constexpr static int MAX_GRID_LINES_NUMBER = 50;
};

} // namespace Gui
} // namespace PowerLab

#endif // GRAPHPARAMETERSMODEL_H
