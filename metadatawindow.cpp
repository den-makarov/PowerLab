#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QToolButton>
#include <QAbstractItemModel>
#include <QStringListModel>
#include <QListView>
#include <QSplitter>

#include "metadatawindow.h"
#include "modelresultmeta.h"

MetaDataWindow::MetaDataWindow(QWidget *parent) : QDialog(parent)
{
  setWindowModality(Qt::ApplicationModal);
  setWindowTitle("Chose signals to plot");
  QSplitter *splitter = new QSplitter;

  QLabel* label = new QLabel(this);
  label->setText("Signals");

  QStringList signal_names;
  signal_names << "One" << "Two" << "Three" << "Four" << "Five";

  model = new QStringListModel(signal_names, this);
  QListView *view = new QListView(this);
  view->setModel(model);
  splitter->addWidget(view);

  QPushButton* ok = new QPushButton(this);
  ok->setText("Ok");
  connect(ok, &QPushButton::pressed, this, &MetaDataWindow::close);
  splitter->addWidget(ok);

  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(label, 0, 0);
  layout->addWidget(splitter, 1, 0);
  setLayout(layout);
}

void MetaDataWindow::loadModelResults(const ModelResultMeta::Data* data) {
  if(!data) {
    E_CRITICAL(this) << "meta data is expected";
    return;
  }

  if(!model) {
    E_CRITICAL(this) << "data model is expected";
    return;
  }

  model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
  int row = 0;

  auto signalsNames = data->signalSet;
  for(auto & item : signalsNames) {
    model->insertRows(row, 1, QModelIndex());
    auto idx = model->index(row, 0, QModelIndex());
    model->setData(idx, item.first);
    row++;
  }
}
