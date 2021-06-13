#ifndef GRAPHPROCESSOR_H
#define GRAPHPROCESSOR_H

#include <vector>
#include <string>
#include <map>
#include <functional>

#include <QWidget>
#include <QBrush>
#include <QPen>

class QPainter;
class QPaintEvent;

namespace Gui {

class GraphProcessor {
public:
  GraphProcessor();

  void paint(QPainter *painter, int elapsed);
  void plot(QPainter *painter,
            const std::vector<double>& x,
            double normalizationFactor) const;

private:
  QBrush m_background;
  QPen m_penOne;
  QPen m_penTwo;
};

class GraphWidget : public QWidget {
public:
  GraphWidget(GraphProcessor *graph, QWidget *parent);

  void addGraphData(std::string name, std::vector<double> dataPoints);

public slots:
  void plot();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  std::map<std::string, const std::vector<double>> m_graphs;
  GraphProcessor* m_graphProcessor;
};

} // namespace Gui
#endif // GRAPHPROCESSOR_H
