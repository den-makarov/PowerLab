#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <vector>
#include <string>
#include <map>
#include <memory>

#include <QWidget>

#include "graphprocessor.h"

class QPainter;
class QPaintEvent;

namespace Gui {

class Plot;

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

  GraphWidget(QWidget *parent = nullptr, GraphProcessor* graph = nullptr);
  ~GraphWidget() override;

  void addGraphData(std::string name,
                    std::string units,
                    std::vector<double>&& dataPoints);
  void addHorizontalScaleData(std::string name,
                              std::string units,
                              std::vector<double>&& dataPoints);

public slots:
  void plot();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  void configureHorizontalScale(Plot& plot);
  void configureVerticalScale(Plot& plot);

  std::vector<GraphData> m_graphs;
  GraphData m_horizontalScale;
  std::unique_ptr<GraphProcessor> m_graphProcessor;

  constexpr static double PLOT_VERTICAL_EXTENSION = 1.2;
  constexpr static double PLOT_HORIZONTAL_EXTENSION = 1.0;
};

} // namespace Gui
#endif // GRAPHWIDGET_H
