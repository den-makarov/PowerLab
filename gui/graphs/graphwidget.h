#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <vector>
#include <string>
#include <map>
#include <memory>

#include <QWidget>

#include "graphprocessor.h"
#include "plot.h"

class QPainter;
class QPaintEvent;
class QRubberBand;

namespace PowerLab {
namespace Gui {

class GraphWidget : public QWidget {
Q_OBJECT
public:
  struct GraphData {
    std::string name;
    std::string units;
    std::vector<double> points;
    double minValue = 0.0;
    double maxValue = 0.0;
  };

  GraphWidget(QWidget *parent = nullptr, GraphProcessor* graph = nullptr, Plot* plot = nullptr);
  ~GraphWidget() override;

  void addGraphData(std::string name,
                    std::string units,
                    std::vector<double>&& dataPoints);
  void addHorizontalScaleData(std::string name,
                              std::string units,
                              std::vector<double>&& dataPoints);

  virtual QSize sizeHint() const override;
public slots:
  void plot();

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  void configureHorizontalScale();
  void configureVerticalScale();
  void setupDefaultPlotMargins() const;

  std::vector<GraphData> m_graphs;
  GraphData m_horizontalScale;
  std::unique_ptr<GraphProcessor> m_graphProcessor;
  std::unique_ptr<Plot> m_plot;

  constexpr static double PLOT_VERTICAL_EXTENSION = 0.1;
  constexpr static double PLOT_HORIZONTAL_EXTENSION = 0.0;

  constexpr static int PREFERRED_WIDGIT_WIDTH_HINT = 500;
  constexpr static int PREFERRED_WIDGIT_HEIGHT_HINT = 300;

  QPoint origin = {0, 0};
  QRubberBand* rubberBand = nullptr;
};

} // namespace Gui
} // namespace PowerLab

#endif // GRAPHWIDGET_H
