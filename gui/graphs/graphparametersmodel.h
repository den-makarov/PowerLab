#ifndef GRAPHPARAMETERSMODEL_H
#define GRAPHPARAMETERSMODEL_H

#include <QObject>
#include <QRectF>
#include <QColor>

namespace PowerLab {
namespace Gui {

class GraphWidget;

class GraphParametersModel final {
  Q_OBJECT
public:
  using GraphDataIdx = size_t;

  enum class GridSide {
    X_SIDE,
    Y_SIDE
  };

  explicit GraphParametersModel(GraphWidget& graph);

  QRectF getValueBounds() const;
  void setValueBounds(QRectF bounds);

  bool isAutoGrid() const;
  void setAutoGrid(bool isAuto);

  int getGridLinesNumber(GridSide side) const;
  void setGridLinesNumber(GridSide side, int number);

  QColor getGridLinesColor() const;
  void setGridLinesColor(QColor color);

  QColor getBackgroundColor() const;
  void setBackgroundColor(QColor color);

  double getGridLinesOrigin(GridSide side) const;
  void setGridLinesOrigin(GridSide side, double origin);
  double getGridLinesEnd(GridSide side) const;
  void setGridLinesEnd(GridSide side, double end);

  GraphDataIdx getGraphNumber() const;

  QColor getGraphColor(GraphDataIdx idx) const;
  void setGraphColor(GraphDataIdx idx, QColor);

  int getLineWidth(GraphDataIdx idx) const;
  void setLineWidth(GraphDataIdx idx, int);

  std::string getGraphName(GraphDataIdx idx) const;
  void setGraphName(GraphDataIdx idx, std::string) const;

  std::string getGraphUnits(GraphDataIdx idx) const;
  void setGraphUnits(GraphDataIdx idx, std::string) const;

  std::string getReferenceName(GraphDataIdx idx) const;
  void setReferencehName(GraphDataIdx idx, std::string) const;

  std::string getReferenceUnits(GraphDataIdx idx) const;
  void setReferenceUnits(GraphDataIdx idx, std::string) const;

private:
  GraphWidget& m_graph;

  constexpr static int MAX_GRID_LINES_NUMBER = 50;
};

} // namespace Gui
} // namespace PowerLab

#endif // GRAPHPARAMETERSMODEL_H
