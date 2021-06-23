#include <QPainter>
#include <QPen>

#include "plot.h"

namespace Gui {

Plot::Plot(int width, int height)
  : m_width(width)
  , m_height(height)
{
  //EMPTY
}

void Plot::setBorder(bool isBorder) {
  m_border = isBorder;
}

void Plot::setMainGridLinesNumber(int xNumber, int yNumber) {
  m_gridXNumber = xNumber;
  m_gridYNumber = yNumber;
}

Plot::ValueBounds& Plot::getBounds() {
  return m_bounds;
}

const Plot::ValueBounds& Plot::getBounds() const {
  return m_bounds;
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

void Plot::setBackground(QColor bgcolor) {
  m_bgcolor = bgcolor;
}

void Plot::addXAxisLabel(const std::string& label) {
  if(m_XLabel.empty()) {
    m_XLabel = label;
  } else {
    m_XLabel += ", " + label;
  }
}

void Plot::addYAxisLabel(const std::string& label) {
  if(m_YLabel.empty()) {
    m_YLabel = label;
  } else {
    m_YLabel += ", " + label;
  }
}

void Plot::update(QPainter* painter) const {
  if(painter == nullptr) {
    return;
  }

  if(m_width <= 0 || m_height <= 0) {
    return;
  }

  painter->fillRect(m_margins.left,
                    m_margins.bottom,
                    m_width - (m_margins.right + m_margins.left),
                    m_height - (m_margins.top + m_margins.bottom),
                    m_bgcolor);

  drawAxisLabels(*painter);
  drawBorder(*painter);
  drawGrid(*painter);
}

void Plot::drawXAxisLabels(QPainter& painter) const {
  if(!m_XLabel.empty()) {
    QRect rect(0,
               m_height - painter.font().pixelSize() - (painter.pen().width() + 4),
               m_width - 2,
               painter.font().pixelSize() + 2);
    painter.drawText(rect, Qt::AlignRight, QString(m_XLabel.c_str()));
  }
}

void Plot::drawYAxisLabels(QPainter& painter) const {
  if(!m_YLabel.empty()) {
    painter.drawText((painter.pen().width() + 1),
                     (painter.pen().width() + 1) + painter.font().pixelSize(),
                     QString(m_YLabel.c_str()));
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

Plot::Margins& Plot::getMargins() {
  return m_margins;
}

const Plot::Margins& Plot::getMargins() const {
  return m_margins;
}

void Plot::drawBorder(QPainter& painter) const {
  if(m_border) {
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawRect(m_margins.left,
                     m_margins.bottom,
                     m_width - (m_margins.right + m_margins.left),
                     m_height - (m_margins.top + m_margins.bottom));
  }
}

void Plot::drawXGrid(QPainter& painter) const {
  if(m_gridXNumber > 0) {
    int step = m_width / (m_gridXNumber + 1);
    double gridLabelStep = (m_bounds.xMax - m_bounds.xMin) / (m_gridXNumber + 1);
    double gridLabel = m_bounds.xMin + gridLabelStep;

    for(int i = step; i < m_width; i += step) {
      painter.drawLine(i, 0, i, m_height);
      drawGridValue(painter, gridLabel, i, m_height);
      gridLabel += gridLabelStep;
    }
  }
}

void Plot::drawYGrid(QPainter& painter) const {
  if(m_gridYNumber > 0) {
    int step = m_height / (m_gridYNumber + 1);
    double gridLabelStep = (m_bounds.yMax - m_bounds.yMin) / (m_gridYNumber + 1);
    double gridLabel = m_bounds.yMax - gridLabelStep;

    for(int i = step; i < m_height; i += step) {
      painter.drawLine(0, i, m_width, i);
      drawGridValue(painter, gridLabel, 0, i + painter.font().pixelSize());
      gridLabel -= gridLabelStep;
    }
  }
}

void Plot::drawGrid(QPainter& painter) const {
  QPen pen({0xB0, 0xB0, 0xB0});
  pen.setWidth(1);
  pen.setStyle(Qt::DashDotLine);
  painter.setPen(pen);

  QFont font;
  font.setPixelSize(12);
  painter.setFont(font);

  drawXGrid(painter);
  drawYGrid(painter);
}

void Plot::drawGridValue(QPainter& painter, double number, int x, int y) const {
  QString str;
  painter.drawText((painter.pen().width() + 1) + x,
                   y - (painter.pen().width() + 1),
                   str.setNum(number, 'g', 3));
}

} // namespace Gui
