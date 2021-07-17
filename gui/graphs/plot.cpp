#include <cmath>

#include <QPainter>
#include <QPen>

#include "plot.h"
#include "logger.h"
#include "math_utils.h"

namespace PowerLab {
namespace Gui {

Plot::Plot(int width, int height)
  : m_width(width)
  , m_height(height)
{
}

int Plot::getWidth() const {
  return m_width;
}

void Plot::setWidth(int width) {
  m_width = width;
}

int Plot::getHeight() const {
  return m_height;
}

void Plot::setHeight(int height) {
  m_height = height;
}

void Plot::setArea(int width, int height) {
  setWidth(width);
  setHeight(height);
}

void Plot::setBorder(bool isBorder) {
  m_border = isBorder;
}

int Plot::getMainGridLinesXNumber() const {
  return m_autoGrid ? -1 : m_gridXNumber;
}

int Plot::getMainGridLinesYNumber() const {
  return m_autoGrid ? -1 : m_gridYNumber;
}

void Plot::setMainGridLinesXNumber(int xNumber) {
  if(!m_autoGrid) {
    m_gridXNumber = xNumber;
  } else {
    Logger::log(GuiMessage::WARNING_SET_PLOT_GRID_LINES_ON_AUTO_GRID);
  }
}

void Plot::setMainGridLinesYNumber(int yNumber) {
  if(!m_autoGrid) {
    m_gridYNumber = yNumber;
  } else {
    Logger::log(GuiMessage::WARNING_SET_PLOT_GRID_LINES_ON_AUTO_GRID);
  }
}

QRectF Plot::getBoundsRect() const {
  return QRectF(m_bounds.xMin,
                m_bounds.yMin,
                m_bounds.xMax - m_bounds.xMin,
                m_bounds.yMax - m_bounds.yMin);
}

Plot::ValueBounds Plot::getBounds() const {
  return m_bounds;
}

bool Plot::isAutoGrid() const {
  return m_autoGrid;
}

void Plot::setAutoGrid(bool enabled) {
  m_autoGrid = enabled;
}

void Plot::setBounds(const ValueBounds& boundaries) {
  m_bounds = boundaries;
}

void Plot::setAxisXLog(bool isLog) {
  m_isXLog = isLog;
}

void Plot::setAxisYLog(bool isLog) {
  m_isYLog = isLog;
}

void Plot::setGridColor(QColor color) {
  m_gridColor = color;
}

QColor Plot::getGridColor() const {
  return m_gridColor;
}

void Plot::setBackground(QColor bgcolor) {
  m_bgcolor = bgcolor;
}

QColor Plot::getBackground() const {
  return m_bgcolor;
}

void Plot::clearXAxisLabels() {
  m_XLabels.clear();
}

void Plot::addXAxisLabel(const std::string& label, QColor textColor) {
  m_XLabels.emplace_back(label, textColor);
}

void Plot::clearYAxisLabels() {
  m_YLabels.clear();
}

void Plot::addYAxisLabel(const std::string& label, QColor textColor) {
  m_YLabels.emplace_back(label, textColor);
}

Plot::ValueBounds Plot::getGridLabelsBounds() const {
  ValueBounds bounds;
  bounds.xMin = m_gridLabelsRect.left();
  bounds.xMax = m_gridLabelsRect.right();
  bounds.yMin = m_gridLabelsRect.bottom();
  bounds.yMax = m_gridLabelsRect.top();
  return bounds;
}

void Plot::setGridLabelsBounds(ValueBounds gridLabels) {
  m_gridLabelsRect.setBottomLeft({gridLabels.xMin, gridLabels.yMin});
  m_gridLabelsRect.setTopRight({gridLabels.xMax, gridLabels.yMax});
}

void Plot::update(QPainter* painter) {
  if(painter == nullptr) {
    return;
  }

  if((m_width - (m_margins.right + m_margins.left)) <= 0
  || (m_height - (m_margins.top + m_margins.bottom)) <= 0) {
    return;
  }

  painter->fillRect(m_margins.left,
                    m_margins.top,
                    m_width - (m_margins.right + m_margins.left),
                    m_height - (m_margins.top + m_margins.bottom),
                    m_bgcolor);

  if(m_autoGrid) {
    calculateGridLinesNumber();
  }

  drawGrid(*painter);
  drawBorder(*painter);
  drawAxisLabels(*painter);
}

void Plot::drawXAxisLabels(QPainter& painter) const {
  if(!m_XLabels.empty()) {
    QRect boundingRect;
    QRect rect(0,
               m_height - m_margins.bottom,
               m_width,
               painter.font().pixelSize() + 2);
    for(auto i = m_XLabels.size(); i != 0; i--) {
      auto& label = m_XLabels[i - 1];

      auto pen = painter.pen();
      pen.setColor(label.textColor);
      painter.setPen(pen);

      painter.drawText(rect, Qt::AlignRight, QString(label.text.c_str()), &boundingRect);
      rect.setWidth(rect.width() - boundingRect.width() - painter.fontMetrics().averageCharWidth() * 2);
    }
  }
}

void Plot::drawYAxisLabels(QPainter& painter) const {
  if(!m_YLabels.empty()) {
    QRect boundingRect;
    QRect rect(m_margins.left,
               0,
               m_width,
               painter.font().pixelSize() + 2);

    for(auto& label : m_YLabels) {
      auto pen = painter.pen();
      pen.setColor(label.textColor);
      painter.setPen(pen);

      painter.drawText(rect,
                       Qt::AlignLeft,
                       QString(label.text.c_str()),
                       &boundingRect);
      rect.setLeft(rect.left() + boundingRect.width() + painter.fontMetrics().averageCharWidth() * 2);
    }
  }
}

void Plot::drawAxisLabels(QPainter& painter) const {
  QPen pen(Qt::black);
  pen.setWidth(1);
  painter.setPen(pen);

  QFont font;
  font.setPixelSize(12);
  painter.setFont(font);

  drawXAxisLabels(painter);
  drawYAxisLabels(painter);
}

void Plot::setMargins(const Margins& margins) {
  m_margins = margins;
}

Plot::Margins Plot::getMargins() const {
  return m_margins;
}

QRect Plot::getMarginsRect() const {
  return QRect(m_margins.left,
               m_margins.top,
               m_width - (m_margins.right + m_margins.left),
               m_height - (m_margins.bottom + m_margins.top));
}

void Plot::drawBorder(QPainter& painter) const {
  if(m_border) {
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawRect(m_margins.left,
                     m_margins.top,
                     m_width - (m_margins.right + m_margins.left),
                     m_height - (m_margins.top + m_margins.bottom));
  }
}

void Plot::calculateGridLinesNumber() {
  m_gridLabelsRect.setLeft(m_bounds.xMin);
  m_gridLabelsRect.setTop(m_bounds.yMax);
  m_gridLabelsRect.setRight(m_bounds.xMax);
  m_gridLabelsRect.setBottom(m_bounds.yMin);

  m_gridXNumber = 0;
  m_gridYNumber = 0;

  int plotWidth = m_width - (m_margins.right + m_margins.left); 
  if(plotWidth > MIN_SPACE_BETWEEN_X_GRID_LINES_PXL) {
    auto segments = Utilities::findOptimalRoundedSegments(m_bounds.xMin,
                                                          m_bounds.xMax,
                                                          plotWidth / MIN_SPACE_BETWEEN_X_GRID_LINES_PXL);

    if(!(std::isnan(segments.from) || std::isnan(segments.to) || std::isnan(segments.step))) {
      m_gridXNumber = static_cast<int>(std::round((segments.to - segments.from) / segments.step));
      m_gridLabelsRect.setLeft(segments.from);
      m_gridLabelsRect.setRight(segments.to);
    }
  }

  int plotHeight = m_height - (m_margins.top + m_margins.bottom);
  if(plotHeight <= MIN_SPACE_BETWEEN_Y_GRID_LINES_PXL) {
  } else {
    auto segments = Utilities::findOptimalRoundedSegments(m_bounds.yMin,
                                                          m_bounds.yMax,
                                                          plotHeight / MIN_SPACE_BETWEEN_Y_GRID_LINES_PXL);

    if(!(std::isnan(segments.from) || std::isnan(segments.to) || std::isnan(segments.step))) {
      m_gridYNumber = static_cast<int>(std::round((segments.to - segments.from) / segments.step));
      m_gridLabelsRect.setBottom(segments.from);
      m_gridLabelsRect.setTop(segments.to);
    }
  }
}

void Plot::drawXGrid(QPainter& painter) const {
  if(m_gridXNumber <= 0) {
    return;
  }

  double factor = (m_width - (m_margins.left + m_margins.right) - 1) / (m_bounds.xMax - m_bounds.xMin);
  double gridLineDist = factor * m_gridLabelsRect.width() / (m_gridXNumber);

  double gridLineLabelStep = m_gridLabelsRect.width() / (m_gridXNumber);
  double gridLineLabel = m_gridLabelsRect.left();

  double left = (m_gridLabelsRect.left() - m_bounds.xMin) * factor + m_margins.left;
  double right = m_gridLabelsRect.right() * factor + m_margins.left;

  auto fontSize = painter.fontMetrics().height();
  auto yPos = m_height - m_margins.bottom + fontSize / 2;

  int cycleLimit = m_gridXNumber;
  while(left < right && cycleLimit >= 0) {
    auto xPos = static_cast<int>(left);

    if(m_margins.left <= xPos && xPos < (m_width - 1) - m_margins.right) {
      painter.drawLine(xPos, m_margins.top, xPos, m_height - m_margins.bottom);

      xPos = static_cast<int>(left - gridLineDist / 2.0);
      QRect textRect(xPos, yPos, static_cast<int>(gridLineDist), fontSize);
      drawGridValue(painter, gridLineLabel, textRect, TextAlign::CENTER);
    }

    left += gridLineDist;
    gridLineLabel += gridLineLabelStep;
    cycleLimit--;
  }
}

void Plot::drawYGrid(QPainter& painter) const {
  if(m_gridYNumber <= 0) {
    return;
  }

  double factor = (m_height - (m_margins.top + m_margins.bottom) - 1) / (m_bounds.yMax - m_bounds.yMin);
  double gridLineDist = factor * std::abs(m_gridLabelsRect.height()) / m_gridYNumber;

  double gridLineLabelStep = std::abs(m_gridLabelsRect.height()) / m_gridYNumber;
  double gridLineLabel = m_gridLabelsRect.bottom();

  double bottom = (m_bounds.yMin - m_gridLabelsRect.bottom()) * factor + m_height - m_margins.bottom;
  double top = m_margins.top;

  auto fontSize = painter.fontMetrics().height();

  int cycleLimit = m_gridYNumber;
  while(bottom > top && cycleLimit >= 0) {
    auto yPos = static_cast<int>(bottom);

    if(m_margins.top < yPos && yPos < m_height - m_margins.bottom) {
      painter.drawLine(m_margins.left, yPos, m_width - m_margins.right, yPos);

      QRect textRect(0, yPos - fontSize / 2, m_margins.left - 1, fontSize);
      drawGridValue(painter, gridLineLabel, textRect, TextAlign::RIGHT);
    }

    bottom -= gridLineDist;
    gridLineLabel += gridLineLabelStep;
    cycleLimit--;
  }
}

void Plot::drawGrid(QPainter& painter) const {
  QPen pen(m_gridColor);
  pen.setWidth(1);
  pen.setStyle(Qt::DashDotLine);
  painter.setPen(pen);

  QFont font;
  font.setPixelSize(12);
  painter.setFont(font);

  drawXGrid(painter);
  drawYGrid(painter);
}

void Plot::drawGridValue(QPainter& painter, double number, QRect textRect, TextAlign align) const {
  QString str;

  if(std::abs(number) <= 10 * std::numeric_limits<double>::epsilon()) {
    str = "0";
  } else {
    str = QString::number(number, 'g', 5);
  }

  auto textAlign = Qt::AlignLeft;
  if(align == TextAlign::CENTER) {
    textAlign = Qt::AlignCenter;
  } else if(align == TextAlign::RIGHT) {
    textAlign = Qt::AlignRight;
  }

  painter.drawText(textRect, textAlign, str);
}

void Plot::dump(std::ostream& out) const {
  out << "Height: " << m_height << " Width: " << m_width;
  out << "\nMargins {left, right, top, bottom} : {"
      << m_margins.left << ", "
      << m_margins.right << ", "
      << m_margins.top << ", "
      << m_margins.bottom << "}\n";
  out << "Bounds {xMax, xMin, yMax, yMin} : {"
      << m_bounds.xMax << ", "
      << m_bounds.xMin << ", "
      << m_bounds.yMax << ", "
      << m_bounds.yMin << "}\n";
  out << "Grid count: Y - " << m_gridYNumber << ", X - " << m_gridXNumber << "\n";

  out << "xLabel:";
  for(auto& label : m_XLabels) {
    out << " " << label.text;
  }

  out << " yLabel:";
  for(auto& label : m_YLabels) {
    out << " " << label.text;
  }
}

std::ostream& operator<<(std::ostream& out, const Plot& plot) {
  plot.dump(out);
  return out;
}

} // namespace Gui
} // namespace PowerLab
