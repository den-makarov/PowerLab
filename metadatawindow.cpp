#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QToolButton>

#include "metadatawindow.h"

MetaDataWindow::MetaDataWindow(QWidget *parent) : QDialog(parent)
{
  setWindowModality(Qt::ApplicationModal);
  setWindowTitle("Chose signals to plot");

  QLabel* label = new QLabel(this);
  label->setText("Signals");

//  QHBoxLayout* hBox = new QHBoxLayout(this);
  QToolButton* one = new QToolButton(this);
  one->setArrowType(Qt::UpArrow);
  QToolButton* two = new QToolButton(this);
  two->setArrowType(Qt::DownArrow);
  QToolButton* three = new QToolButton(this);
  three->setArrowType(Qt::LeftArrow);

  one->setDown(true);
//  hBox->addWidget(one);
//  hBox->addWidget(two);
//  hBox->addWidget(three);


  QPushButton* ok = new QPushButton(this);
  ok->setText("Ok");
  connect(ok, &QPushButton::pressed, this, &MetaDataWindow::close);

  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(label, 0, 0);
//  layout->addLayout(hBox, 1, 1);
  layout->addWidget(one, 1, 1);
  layout->addWidget(two, 1, 2);
  layout->addWidget(three, 1, 3);
  layout->addWidget(ok, 2, 0);
  setLayout(layout);
}
