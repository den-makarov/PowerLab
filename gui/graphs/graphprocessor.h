#ifndef GRAPHPROCESSOR_H
#define GRAPHPROCESSOR_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QVector>

#include "backend/logger/logger.h"

class QPainter;
class QPaintEvent;

class GraphProcessor
{
public:
  GraphProcessor();
  ~GraphProcessor() {
//    E_DEBUG(nullptr) << "Graph proc destructor";
  }
  void paint(QPainter *painter, int elapsed);
  void plot(QPainter *painter, QVector<double> x, double max);

private:
  QBrush background;
  QPen penOne;
  QPen penTwo;
};

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(GraphProcessor *graph, QWidget *parent);
  virtual ~Widget() override {
//    E_DEBUG(nullptr) << "Widget destructor";
  }
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

#endif // GRAPHPROCESSOR_H
