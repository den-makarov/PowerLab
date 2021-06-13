#ifndef PLOT_H
#define PLOT_H

#include <cstdlib>
#include <vector>
#include <string>

#include <QColor>

class QPainter;

namespace Gui {

class Plot {
public:
  enum class Axis {
    X,
    Y
  };

  struct Bounds {
    double xMax;
    double xMin;
    double yMax;
    double yMin;
  };

  Plot(int width, int height);
  Plot(int width,
       int height,
       bool border,
       int gridWidth = 0,
       int gridHeight = 0);

  void setBackground(uint8_t R = 0xFF, uint8_t G = 0xFF, uint8_t B = 0xFF) {
    m_background[0] = R;
    m_background[1] = G;
    m_background[2] = B;
  }

  void setAxisLabel(const Axis& axis, const std::string& label) {
    if(axis == Axis::X) {
      m_axisLabels[0] = label;
    } else {
      m_axisLabels[1] = label;
    }
  }

  void setBounds(const Bounds& boundaries) {
    m_bounds = boundaries;
  }

  void setLogarithmic(const Axis& axis, bool isLog) {
    if(axis == Axis::X) {
      m_isWidthLogarithmic = isLog;
    } else {
      m_isHeightLogarithmic = isLog;
    }
  }

  void update(QPainter* painter) const;

private:
  struct Graph {
    std::vector<int> graph;
    QColor color;
  };

  const int m_width;
  const int m_height;
  bool m_border;
  bool m_isWidthLogarithmic = false;
  bool m_isHeightLogarithmic = false;
  int m_gridWidth;
  int m_gridHeight;
  Bounds m_bounds = {0.6, 0.0, 0.12, -0.12};
  std::string m_axisLabels[2] = {"", ""};
  uint8_t m_background[3] = {0xFF, 0xFF, 0xA0};
  std::vector<Graph> m_graphs;

  void drawBorder(QPainter* painter) const;
  void drawGrid(QPainter* painter) const;
  void drawAxisLabels(QPainter* painter) const;
  void drawGridValue(QPainter* painter, double number, int x, int y) const;
};

} // namespace Gui
#endif // PLOT_H
