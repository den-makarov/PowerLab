#ifndef METADATAWINDOW_H
#define METADATAWINDOW_H

#include <QDialog>

#include "modelresult/modelresultmeta.h"


class QAbstractItemModel;
class QListView;

namespace Gui {

class MetaDataWindow : public QDialog {
public:
  explicit MetaDataWindow(QWidget *parent = nullptr);

  QAbstractItemModel* loadModelResults(const Model::ModelResultMeta::Data* data);

private:
  constexpr static size_t MIN_WINDOW_WIDTH = 500;
  constexpr static size_t MIN_WINDOW_HEIGHT = 400;
  QAbstractItemModel *signals_model = nullptr;
  QAbstractItemModel *graph_model = nullptr;
  QListView *signals_view = nullptr;
  QListView *graph_view = nullptr;

private slots:
  void addSignalToGraph();
  void removeSignalFromGraph();
};

} // namespace Gui

#endif // METADATAWINDOW_H
