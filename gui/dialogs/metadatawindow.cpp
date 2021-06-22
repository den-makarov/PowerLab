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
#include "modelresult/modelresult.h"

namespace Gui {

MetaDataWindow::MetaDataWindow(QWidget *parent) : QDialog(parent)
{
  setWindowModality(Qt::ApplicationModal);
  setWindowTitle("Chose signals to plot");

  QLabel* label = new QLabel(this);
  label->setText("Signals");

  QSplitter* signals_splitter = new QSplitter(this);

  m_signalsModel = new QStringListModel(this);
  m_signalsView = new QListView(this);
  m_signalsView->setModel(m_signalsModel);

  m_graphModel = new QStringListModel(this);
  m_graphView = new QListView(this);
  m_graphView->setModel(m_graphModel);

  signals_splitter->addWidget(m_signalsView);
  signals_splitter->addWidget(m_graphView);

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

  QGridLayout* grid = new QGridLayout(this);

  QGridLayout* button_layout = new QGridLayout();
  grid->addLayout(button_layout, 2, 0);
  grid->addWidget(label, 0, 0);
  grid->addWidget(signals_splitter, 1, 0);

  button_layout->addWidget(add_signal, 0, 0, Qt::AlignLeft);
  button_layout->addWidget(del_signal, 0, 1, Qt::AlignLeft);
  button_layout->addWidget(ok, 1, 2, Qt::AlignRight);
  button_layout->addWidget(cancel, 1, 3, Qt::AlignRight);
}

QAbstractItemModel* MetaDataWindow::loadModelResults(const Model::ModelResult& modelResults) {
  m_signalsModel->removeRows(0, m_signalsModel->rowCount());
  int row = 0;

  // Skip 0-index signal, cause it is horizontal scale. No need to select
  for(auto& signalName : modelResults.getAllSignalNames()) {
    m_signalsModel->insertRows(row, 1);
    auto idx = m_signalsModel->index(row, 0);
    m_signalsModel->setData(idx, QString::fromStdString(signalName));
    row++;
  }

  return m_graphModel;
}

void MetaDataWindow::addSignalToGraph() {
  QItemSelectionModel *selectionModel = m_signalsView->selectionModel();
  if(!selectionModel) {
    Logger::log(GuiMessage::ERROR_SELECTION_INVALID);
    return;
  }

  const QModelIndexList indexes = selectionModel->selectedIndexes();

  for(const QModelIndex &idx : indexes) {
    auto data = idx.data();
    if(data.isValid()) {
      auto startIdx = m_graphModel->index(0, 0);
      auto matches = m_graphModel->match(startIdx, Qt::DisplayRole, data, 1, Qt::MatchExactly);
      if(matches.isEmpty()) {
        m_graphModel->insertRow(m_graphModel->rowCount());
        auto row_idx = m_graphModel->index(m_graphModel->rowCount() - 1, 0);
        m_graphModel->setData(row_idx, data);
      } else {
        Logger::log(GuiMessage::DEBUG_ATTEMPT_ADD_ITEM_TWICE, data.toString().toStdString());
      }
    }
  }

  selectionModel->clearSelection();
}

void MetaDataWindow::removeSignalFromGraph() {
  QItemSelectionModel *selectionModel = m_graphView->selectionModel();
  if(!selectionModel) {
    Logger::log(GuiMessage::ERROR_SELECTION_INVALID);
    return;
  }

  const QModelIndexList indexes = selectionModel->selectedIndexes();

  for(const QModelIndex &idx : indexes) {
    m_graphModel->removeRow(idx.row());
  }

  selectionModel->clearSelection();
}

} // namespace Gui
