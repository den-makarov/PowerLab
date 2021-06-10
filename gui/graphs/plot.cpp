#include <QPainter>
#include <QPen>

#include "plot.h"

namespace Gui {

Plot::Plot(int width, int height)
  : mWidth(width)
  , mHeight(height)
  , mBorder(false)
  , mGridWidth(0)
  , mGridHeight(0)
{
  //EMPTY
}

Plot::Plot(int width, int height, bool border, int gridWidth, int gridHeight)
  : mWidth(width)
  , mHeight(height)
  , mBorder(border)
  , mGridWidth(gridWidth)
  , mGridHeight(gridHeight)
{
  //EMPTY
}

void Plot::Update(QPainter* painter) const {
  if(painter == nullptr) {
    return;
  }

  if(mWidth <= 0 || mHeight <= 0) {
    return;
  }

  painter->fillRect(0, 0, mWidth, mHeight, QColor(mBackground[0], mBackground[1], mBackground[2]));
  DrawAxisLabels(painter);
  DrawBorder(painter);
  DrawGrid(painter);
}

void Plot::DrawAxisLabels(QPainter *painter) const {
  if(painter == nullptr) {
    return;
  }

  const auto & xLabel = mAxisLabels[0];
  const auto & yLabel = mAxisLabels[1];

  if(!xLabel.empty()) {
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);
    QRect tRect(0, mHeight - font.pixelSize() - (pen.width() + 4), mWidth - 2, font.pixelSize() + 2);
    painter->drawText(tRect, Qt::AlignRight, QString(xLabel.c_str()));
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

void Plot::DrawBorder(QPainter* painter) const {
  if(painter == nullptr) {
    return;
  }

  if(mBorder) {
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawRect(0, 0, mWidth, mHeight);
  }
}

void Plot::DrawGrid(QPainter* painter) const {
  if(painter == nullptr) {
    return;
  }

  if(mGridWidth > 0) {
    QPen pen({0xB0, 0xB0, 0xB0});
    pen.setWidth(1);
    pen.setStyle(Qt::DashDotLine);
    painter->setPen(pen);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);

    int step = mWidth / (mGridWidth + 1);
    double gridLabelStep = (mBounds.xMax - mBounds.xMin) / (mGridWidth + 1);
    double gridLabel = mBounds.xMin + gridLabelStep;

    for(int i = step; i < mWidth; i += step) {
      painter->drawLine(i, 0, i, mHeight);
      DrawGridValue(painter, gridLabel, i, mHeight);
      gridLabel += gridLabelStep;
    }
  }

  if(mGridHeight > 0) {
    QPen pen({0xB0, 0xB0, 0xB0});
    pen.setWidth(1);
    pen.setStyle(Qt::DashDotLine);
    painter->setPen(pen);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);

    int step = mHeight / (mGridHeight + 1);
    double gridLabelStep = (mBounds.yMax - mBounds.yMin) / (mGridHeight + 1);
    double gridLabel = mBounds.yMax - gridLabelStep;

    for(int i = step; i < mHeight; i += step) {
      painter->drawLine(0, i, mWidth, i);
      DrawGridValue(painter, gridLabel, 0, i + font.pixelSize());
      gridLabel -= gridLabelStep;
    }
  }
}

void Plot::DrawGridValue(QPainter* painter, double number, int x, int y) const {
  if(painter == nullptr) {
    return;
  }

  QString str;
  painter->drawText((painter->pen().width() + 1) + x,
                    y - (painter->pen().width() + 1),
                    str.setNum(number, 'f', 2));
}

} // namespace Gui
