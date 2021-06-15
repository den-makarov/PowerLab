#include <QPainter>
#include <QPen>

#include "plot.h"

namespace Gui {

Plot::Plot(int width, int height)
  : m_width(width)
  , m_height(height)
  , m_border(false)
  , m_gridWidth(0)
  , m_gridHeight(0)
{
  //EMPTY
}

Plot::Plot(int width, int height, bool border, int gridWidth, int gridHeight)
  : m_width(width)
  , m_height(height)
  , m_border(border)
  , m_gridWidth(gridWidth)
  , m_gridHeight(gridHeight)
{
  //EMPTY
}

void Plot::update(QPainter* painter) const {
  if(painter == nullptr) {
    return;
  }

  if(m_width <= 0 || m_height <= 0) {
    return;
  }

  QColor bgColor(m_background[0], m_background[1], m_background[2]);
  painter->fillRect(0, 0, m_width, m_height, bgColor);
  drawAxisLabels(painter);
  drawBorder(painter);
  drawGrid(painter);
}

void Plot::drawAxisLabels(QPainter *painter) const {
  if(painter == nullptr) {
    return;
  }

  const auto& xLabel = m_axisLabels.first;
  const auto& yLabel = m_axisLabels.second;

  if(!xLabel.empty()) {
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);
    QRect rect(0, m_height - font.pixelSize() - (pen.width() + 4), m_width - 2, font.pixelSize() + 2);
    painter->drawText(rect, Qt::AlignRight, QString(xLabel.c_str()));
  }

  if(!yLabel.empty()) {
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);
    painter->drawText((pen.width() + 1),
                      (pen.width() + 1) + font.pixelSize(),
                      QString(yLabel.c_str()));
  }
}

void Plot::drawBorder(QPainter* painter) const {
  if(painter == nullptr) {
    return;
  }

  if(m_border) {
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawRect(0, 0, m_width, m_height);
  }
}

void Plot::drawGrid(QPainter* painter) const {
  if(painter == nullptr) {
    return;
  }

  if(m_gridWidth > 0) {
    QPen pen({0xB0, 0xB0, 0xB0});
    pen.setWidth(1);
    pen.setStyle(Qt::DashDotLine);
    painter->setPen(pen);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);

    int step = m_width / (m_gridWidth + 1);
    double gridLabelStep = (m_bounds.xMax - m_bounds.xMin) / (m_gridWidth + 1);
    double gridLabel = m_bounds.xMin + gridLabelStep;

    for(int i = step; i < m_width; i += step) {
      painter->drawLine(i, 0, i, m_height);
      drawGridValue(painter, gridLabel, i, m_height);
      gridLabel += gridLabelStep;
    }
  }

  if(m_gridHeight > 0) {
    QPen pen({0xB0, 0xB0, 0xB0});
    pen.setWidth(1);
    pen.setStyle(Qt::DashDotLine);
    painter->setPen(pen);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);

    int step = m_height / (m_gridHeight + 1);
    double gridLabelStep = (m_bounds.yMax - m_bounds.yMin) / (m_gridHeight + 1);
    double gridLabel = m_bounds.yMax - gridLabelStep;

    for(int i = step; i < m_height; i += step) {
      painter->drawLine(0, i, m_width, i);
      drawGridValue(painter, gridLabel, 0, i + font.pixelSize());
      gridLabel -= gridLabelStep;
    }
  }
}

void Plot::drawGridValue(QPainter* painter, double number, int x, int y) const {
  if(painter == nullptr) {
    return;
  }

  QString str;
  painter->drawText((painter->pen().width() + 1) + x,
                    y - (painter->pen().width() + 1),
                    str.setNum(number, 'g', 3));
}

} // namespace Gui
