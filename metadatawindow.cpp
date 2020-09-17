#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

#include "metadatawindow.h"

MetaDataWindow::MetaDataWindow(QWidget *parent) : QWidget(parent, Qt::Tool)
{
  setWindowModality(Qt::ApplicationModal);
  setWindowTitle("Chose signals to plot");
  setMinimumSize(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT);

  QLabel* label = new QLabel(this);
  label->setText("Signals");

  QPushButton* ok = new QPushButton(this);
  ok->setText("Ok");
  connect(ok, &QPushButton::pressed, this, &MetaDataWindow::close);

  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(label, 0, 0);
  layout->addWidget(ok, 1, 4);
  setLayout(layout);
}
