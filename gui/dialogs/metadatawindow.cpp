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

#include "logger.h"
#include "metadatawindow.h"
#include "modelresult/modelresultmeta.h"

namespace Gui {

/**
 * @brief MetaDataWindow::MetaDataWindow
 * @param parent
 */
MetaDataWindow::MetaDataWindow(QWidget *parent) : QDialog(parent)
{
  setWindowModality(Qt::ApplicationModal);
  setWindowTitle("Chose signals to plot");

  QLabel* label = new QLabel(this);
  label->setText("Signals");

  QSplitter *signals_splitter = new QSplitter(this);

  signals_model = new QStringListModel(this);
  signals_view = new QListView(this);
  signals_view->setModel(signals_model);

  graph_model = new QStringListModel(this);
  graph_view = new QListView(this);
  graph_view->setModel(graph_model);

  signals_splitter->addWidget(signals_view);
  signals_splitter->addWidget(graph_view);

  QPushButton* ok = new QPushButton(this);
  ok->setText("&Ok");
  ok->setMaximumWidth(80);
  connect(ok, &QPushButton::pressed, this, &MetaDataWindow::accept);

  QPushButton* cancel = new QPushButton(this);
  cancel->setText("&Cancel");
  cancel->setMaximumWidth(80);
  connect(cancel, &QPushButton::pressed, this, &MetaDataWindow::reject);

  QPushButton* add_signal = new QPushButton(this);
  add_signal->setText("&Add");
  add_signal->setMaximumWidth(80);
  connect(add_signal, &QPushButton::pressed, this, &MetaDataWindow::addSignalToGraph);

  QPushButton* del_signal = new QPushButton(this);
  del_signal->setText("&Remove");
  del_signal->setMaximumWidth(80);
  connect(del_signal, &QPushButton::pressed, this, &MetaDataWindow::removeSignalFromGraph);

  QGridLayout *layout = new QGridLayout();
  setLayout(layout);

  QGridLayout *button_layout = new QGridLayout();
  layout->addLayout(button_layout, 2, 0);
  layout->addWidget(label, 0, 0);
  layout->addWidget(signals_splitter, 1, 0);

  button_layout->addWidget(add_signal, 0, 0, Qt::AlignLeft);
  button_layout->addWidget(del_signal, 0, 1, Qt::AlignLeft);
  button_layout->addWidget(ok, 1, 2, Qt::AlignRight);
  button_layout->addWidget(cancel, 1, 3, Qt::AlignRight);
}

/**
 * @brief MetaDataWindow::loadModelResults
 * @param data
 */
QAbstractItemModel* MetaDataWindow::loadModelResults(const Model::ModelResultMeta::Data* data) {
  if(!data) {
    Logger::log(GuiMessage::ERROR_NO_META_DATA);
    return nullptr;
  }

  signals_model->removeRows(0, signals_model->rowCount());
  int row = 0;

  auto signalsNames = data->signalSet;
  for(auto & item : signalsNames) {
    signals_model->insertRows(row, 1);
    auto idx = signals_model->index(row, 0);
    signals_model->setData(idx, QString::fromStdString(item.name));
    row++;
  }

  return graph_model;
}

/**
 * @brief MetaDataWindow::addSignalToGraph
 */
void MetaDataWindow::addSignalToGraph() {
  QItemSelectionModel *selectionModel = signals_view->selectionModel();
  if(!selectionModel) {
    Logger::log(GuiMessage::ERROR_SELECTION_INVALID);
    return;
  }

  const QModelIndexList indexes = selectionModel->selectedIndexes();

  for(const QModelIndex &idx : indexes) {
    auto data = idx.data();
    if(data.isValid()) {
      auto startIdx = graph_model->index(0, 0);
      auto matches = graph_model->match(startIdx, Qt::DisplayRole, data, 1, Qt::MatchExactly);
      if(matches.isEmpty()) {
        graph_model->insertRow(graph_model->rowCount());
        auto row_idx = graph_model->index(graph_model->rowCount() - 1, 0);
        graph_model->setData(row_idx, data);
      } else {
        Logger::log(GuiMessage::DEBUG_ATTEMPT_ADD_ITEM_TWICE, data.toString().toStdString());
      }
    }
  }

  selectionModel->clearSelection();
}

/**
 * @brief MetaDataWindow::removeSignalFromGraph
 */
void MetaDataWindow::removeSignalFromGraph() {
  QItemSelectionModel *selectionModel = graph_view->selectionModel();
  if(!selectionModel) {
    Logger::log(GuiMessage::ERROR_SELECTION_INVALID);
    return;
  }

  const QModelIndexList indexes = selectionModel->selectedIndexes();

  for(const QModelIndex &idx : indexes) {
    graph_model->removeRow(idx.row());
  }

  selectionModel->clearSelection();
}

} // namespace Gui
