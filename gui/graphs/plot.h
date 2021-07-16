#ifndef PLOT_H
#define PLOT_H

#include <cstdlib>
#include <vector>
#include <string>

#include <QColor>
#include <QRect>

class QPainter;

namespace PowerLab {
namespace Gui {

class Plot {
public:
  enum class TextAlign {
    LEFT,
    CENTER,
    RIGHT
  };

  struct ValueBounds {
    double xMax;
    double xMin;
    double yMax;
    double yMin;
  };

  struct Margins {
    int left;
    int right;
    int top;
    int bottom;
  };

  Plot(int width = 0, int height = 0);

  void setWidth(int width);
  int getWidth() const;
  void setHeight(int height);
  int getHeight() const;
  void setArea(int width, int height);

  void setBackground(QColor bgcolor);
  QColor getBackground() const;

  void setGridColor(QColor bgcolor);
  QColor getGridColor() const;

  void setBounds(const ValueBounds& boundaries);
  ValueBounds getBounds() const;
  QRectF getBoundsRect() const;

  void setMargins(const Margins& boundaries);
  Margins getMargins() const;
  QRect getMarginsRect() const;

  void setAxisXLog(bool isLog);
  void setAxisYLog(bool isLog);

  void addXAxisLabel(const std::string& label, QColor textColor = Qt::black);
  void clearXAxisLabels();

  void addYAxisLabel(const std::string& label, QColor textColor = Qt::black);
  void clearYAxisLabels();

  void setAutoGrid(bool enabled);
  bool isAutoGrid() const;

  void setMainGridLinesXNumber(int xNumber);
  void setMainGridLinesYNumber(int yNumber);
  int getMainGridLinesXNumber() const;
  int getMainGridLinesYNumber() const;

  ValueBounds getGridLabelsBounds() const;
  void setGridLabelsBounds(ValueBounds gridLabels);

  void setBorder(bool isBorder);

  void update(QPainter* painter);
private:
  struct AxisLabel {
    AxisLabel(const std::string& label, QColor color)
    : text(label)
    , textColor(color)
    {}
    std::string text;
    QColor textColor;
  };

  friend std::ostream& operator<<(std::ostream&, const Plot& plot);
  void dump(std::ostream& out) const;
  void drawBorder(QPainter& painter) const;

  void drawGrid(QPainter& painter) const;
  void drawXGrid(QPainter& painter) const;
  void drawYGrid(QPainter& painter) const;

  void drawAxisLabels(QPainter& painter) const;
  void drawXAxisLabels(QPainter& painter) const;
  void drawYAxisLabels(QPainter& painter) const;

  void drawGridValue(QPainter& painter,
                     double number,
                     QRect textRect,
                     TextAlign align = TextAlign::LEFT) const;

  void calculateGridLinesNumber();

  int m_width;
  int m_height;
  bool m_border = true;
  bool m_autoGrid = true;
  bool m_isXLog = false;
  bool m_isYLog = false;
  int m_gridXNumber = 0;
  int m_gridYNumber = 0;
  QRectF m_gridLabelsRect;
  ValueBounds m_bounds = {1.0, -1.0, 1.0, -1.0};
  Margins m_margins = {0, 0, 0, 0};
  std::vector<AxisLabel> m_XLabels;
  std::vector<AxisLabel> m_YLabels;
  QColor m_bgcolor = Qt::white;
  QColor m_gridColor = {0xB0, 0xB0, 0xB0};

  static constexpr int MIN_SPACE_BETWEEN_X_GRID_LINES_PXL = 100;
  static constexpr int MIN_SPACE_BETWEEN_Y_GRID_LINES_PXL = 20;
};

std::ostream& operator<<(std::ostream& out, const Plot& plot);

} // namespace Gui
} // namespace PowerLab

#endif // PLOT_H
