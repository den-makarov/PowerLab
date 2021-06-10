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
  QBrush background;
  QPen penOne;
  QPen penTwo;
};

class Widget : public QWidget {
public:
  Widget(GraphProcessor *graph, QWidget *parent);

  void setNames(QStringList names);

public slots:
  void plot();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  QStringList m_names;
  GraphProcessor *graph;
  QVector<double> lineV;
  QVector<double> lineI;
  double maxV = 0.0;
  double maxI = 0.0;
};

} // namespace Gui
#endif // GRAPHPROCESSOR_H
