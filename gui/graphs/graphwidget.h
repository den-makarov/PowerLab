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
    std::string units;
    std::vector<double> points;
    double minValue = 0.0;
    double maxValue = 0.0;
  };

  GraphWidget(QWidget *parent = nullptr, GraphProcessor* graph = nullptr);

  void addGraphData(std::string name,
                    std::string units,
                    std::vector<double> dataPoints);
  void addHorizontalScaleData(std::string name,
                              std::string units,
                              std::vector<double> dataPoints);

public slots:
  void plot();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  void configureHorizontalScale(Plot& plot);
  void configureVerticalScale(Plot& plot);

  std::map<std::string, GraphData> m_graphs;
  std::pair<std::string, GraphData> m_horizontalScale;
  std::unique_ptr<GraphProcessor> m_graphProcessor;
};

} // namespace Gui
#endif // GRAPHWIDGET_H
