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

  Plot(int width, int height);

  int getWidth() const;
  int getHeight() const;

  void setBackground(QColor bgcolor);
  const QColor& getBackground() const;
  QColor& getBackground();

  void setBounds(const ValueBounds& boundaries);
  ValueBounds& getBounds();
  const ValueBounds& getBounds() const;

  void setMargins(const Margins& boundaries);
  Margins& getMargins();
  const Margins& getMargins() const;

  void setAxisXLog(bool isLog);
  void setAxisYLog(bool isLog);

  void addXAxisLabel(const std::string& label);
  void addYAxisLabel(const std::string& label);

  void setMainGridLinesNumber(int xNumber, int yNumber);
  void setBorder(bool isBorder);

  void update(QPainter* painter) const;
private:
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

  const int m_width;
  const int m_height;
  bool m_border = false;
  bool m_isXLog = false;
  bool m_isYLog = false;
  int m_gridXNumber = 0;
  int m_gridYNumber = 0;
  ValueBounds m_bounds = {0.6, 0.0, 0.12, -0.12};
  Margins m_margins = {0, 0, 0, 0};
  std::string m_XLabel = "";
  std::string m_YLabel = "";
  QColor m_bgcolor = Qt::white;
};

std::ostream& operator<<(std::ostream& out, const Plot& plot);

} // namespace Gui
} // namespace PowerLab

#endif // PLOT_H
