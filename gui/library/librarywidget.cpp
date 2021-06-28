#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>

#include "librarywidget.h"

LibraryWidget::LibraryWidget(QWidget *parent) : QWidget(parent) {
  QGridLayout* grid = new QGridLayout(this);
  grid->addWidget(new QPushButton("Close", this), 0, 0, Qt::AlignCenter);
  grid->addWidget(new QCheckBox("Click me", this), 1, 0, Qt::AlignCenter);
}
