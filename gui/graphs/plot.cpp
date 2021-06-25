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

int Plot::getWidth() const {
  return m_width;
}

int Plot::getHeight() const {
  return m_height;
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

  drawBorder(*painter);
  drawGrid(*painter);
  drawAxisLabels(*painter);
}

void Plot::drawXAxisLabels(QPainter& painter) const {
  if(!m_XLabel.empty()) {
    QRect rect(0,
               m_height - m_margins.bottom,
               m_width,
               painter.font().pixelSize() + 2);
    painter.drawText(rect, Qt::AlignRight, QString(m_XLabel.c_str()));
  }
}

void Plot::drawYAxisLabels(QPainter& painter) const {
  if(!m_YLabel.empty()) {
    painter.drawText(m_margins.left,
                     m_margins.top - 4,
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
    int distBetweenGridLines = (m_width - (m_margins.left + m_margins.right)) / (m_gridXNumber + 1);
    double gridLineLabelStep = (m_bounds.xMax - m_bounds.xMin) / (m_gridXNumber + 1);
    double gridLineLabel = m_bounds.xMin + gridLineLabelStep;

    int leftLimit = distBetweenGridLines + m_margins.left;
    int rightLimit = m_width - (m_margins.left + m_margins.right);

    for(int i = leftLimit; i < rightLimit; i += distBetweenGridLines) {
      painter.drawLine(i, m_margins.bottom, i, m_height - m_margins.top);

      auto gridLabelYOffset = m_height - m_margins.top;
      auto gridLabelXOffset = i;

      if(m_border) {
        gridLabelYOffset += 2;
      }

      QRect textRect(gridLabelXOffset - distBetweenGridLines / 2,
                     gridLabelYOffset,
                     distBetweenGridLines,
                     painter.font().pixelSize());

      drawGridValue(painter, gridLineLabel, textRect, TextAlign::CENTER);
      gridLineLabel += gridLineLabelStep;
    }
  }
}

void Plot::drawYGrid(QPainter& painter) const {
  if(m_gridYNumber > 0) {
    double distBetweenGridLines = (m_height - (m_margins.top + m_margins.bottom) - 1) * 1.0 / (m_gridYNumber + 1.0);
    double gridLineLabelStep = (m_bounds.yMax - m_bounds.yMin) / (m_gridYNumber + 1.0);
    double gridLineLabel = m_bounds.yMax - gridLineLabelStep;

    double topLimit = distBetweenGridLines + m_margins.top;
    double bottomLimit = m_height - (m_margins.top + m_margins.bottom);

    for(double i = topLimit; i < bottomLimit; i += distBetweenGridLines) {
      auto y = static_cast<int>(i);
      painter.drawLine(m_margins.left, y, m_width - m_margins.right, y);

      auto gridLabelYOffset = y;
      auto gridLabelXOffset = 0;

      QRect textRect(gridLabelXOffset,
                     gridLabelYOffset - painter.font().pixelSize() / 2,
                     m_margins.left - 1,
                     painter.font().pixelSize());

      drawGridValue(painter, gridLineLabel, textRect, TextAlign::RIGHT);

      gridLineLabel -= gridLineLabelStep;
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

void Plot::drawGridValue(QPainter& painter, double number, QRect textRect, TextAlign align) const {
  QString str = QString::number(number, 'g', 2);

  auto textAlign = Qt::AlignLeft;
  if(align == TextAlign::CENTER) {
    textAlign = Qt::AlignCenter;
  } else if(align == TextAlign::RIGHT) {
    textAlign = Qt::AlignRight;
  }

  painter.drawText(textRect, textAlign, str);
}

} // namespace Gui
