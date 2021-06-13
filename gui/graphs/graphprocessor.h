#ifndef GRAPHPROCESSOR_H
#define GRAPHPROCESSOR_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QVector>

class QPainter;
class QPaintEvent;

namespace Gui {

class GraphProcessor {
public:
  GraphProcessor();

  void paint(QPainter *painter, int elapsed);
  void plot(QPainter *painter, QVector<double> x, double max);

private:
  QBrush m_background;
  QPen m_penOne;
  QPen m_penTwo;
};

class GraphWidget : public QWidget {
public:
  GraphWidget(GraphProcessor *graph, QWidget *parent);

  void setNames(QStringList names);

public slots:
  void plot();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  QStringList m_names;
  GraphProcessor* m_graphProcessor;
  QVector<double> m_lineV;
  QVector<double> m_lineI;
  double m_maxV = 0.0;
  double m_maxI = 0.0;
};

} // namespace Gui
#endif // GRAPHPROCESSOR_H
