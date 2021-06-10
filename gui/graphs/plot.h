#ifndef PLOT_H
#define PLOT_H

#include <cstdlib>
#include <vector>
#include <string>

#include <QColor>

class QPainter;

namespace Gui {

class Plot
{
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

  void SetBackground(uint8_t R = 0xFF, uint8_t G = 0xFF, uint8_t B = 0xFF) {
    mBackground[0] = R;
    mBackground[1] = G;
    mBackground[2] = B;
  }

  void SetAxisLabel(const Axis& axis, const std::string& label) {
    if(axis == Axis::X) {
      mAxisLabels[0] = label;
    } else {
      mAxisLabels[1] = label;
    }
  }

  void SetBounds(const Bounds& boundaries) {
    mBounds = boundaries;
  }

  void SetLogarithmic(const Axis& axis, bool isLog) {
    if(axis == Axis::X) {
      isWidthLogarithmic = isLog;
    } else {
      isHeightLogarithmic = isLog;
    }
  }

  void Update(QPainter* painter) const;

private:
  struct Graph {
    std::vector<int> graph;
    QColor color;
  };

  const int mWidth;
  const int mHeight;
  bool mBorder;
  bool isWidthLogarithmic = false;
  bool isHeightLogarithmic = false;
  int mGridWidth;
  int mGridHeight;
  Bounds mBounds = {0.6, 0.0, 0.12, -0.12};
  std::string mAxisLabels[2] = {"", ""};
  uint8_t mBackground[3] = {0xFF, 0xFF, 0xA0};
  std::vector<Graph> graphs;

  void DrawBorder(QPainter* painter) const;
  void DrawGrid(QPainter* painter) const;
  void DrawAxisLabels(QPainter* painter) const;
  void DrawGridValue(QPainter* painter, double number, int x, int y) const;
};

} // namespace Gui
#endif // PLOT_H
