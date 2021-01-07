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

  QLabel* label = new QLabel(this);
  label->setText("Signals");

  QSplitter *signals_splitter = new QSplitter(this);

  signals_model = new QStringListModel(this);
  QListView *signals_view = new QListView(this);
  signals_view->setModel(signals_model);

  QStringList dummy;
  dummy << "one" << "two" << "three";

  graph_model = new QStringListModel(dummy, this);
  QListView *graph_view = new QListView(this);
  graph_view->setModel(graph_model);

  signals_splitter->addWidget(signals_view);
  signals_splitter->addWidget(graph_view);

  QPushButton* ok = new QPushButton(this);
  ok->setText("&Ok");
  ok->setMaximumWidth(80);
  connect(ok, &QPushButton::pressed, this, &MetaDataWindow::close);

  QPushButton* cancel = new QPushButton(this);
  cancel->setText("&Cancel");
  cancel->setMaximumWidth(80);
  connect(cancel, &QPushButton::pressed, this, &MetaDataWindow::close);

  QGridLayout *layout = new QGridLayout(this);
  setLayout(layout);

  QGridLayout *button_layout = new QGridLayout(this);
  layout->addLayout(button_layout, 2, 0, Qt::AlignRight);
  layout->addWidget(label, 0, 0);
  layout->addWidget(signals_splitter, 1, 0);

  button_layout->addWidget(ok, 0, 0);
  button_layout->addWidget(cancel, 0, 1);
}

void MetaDataWindow::loadModelResults(const ModelResultMeta::Data* data) {
  if(!data) {
    E_CRITICAL(this) << "meta data is expected";
    return;
  }

  if(!signals_model) {
    E_CRITICAL(this) << "data model is expected";
    return;
  }

  signals_model->removeRows(0, signals_model->rowCount(QModelIndex()), QModelIndex());
  int row = 0;

  auto signalsNames = data->signalSet;
  for(auto & item : signalsNames) {
    signals_model->insertRows(row, 1, QModelIndex());
    auto idx = signals_model->index(row, 0, QModelIndex());
    signals_model->setData(idx, item.first);
    row++;
  }
}
