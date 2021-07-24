#ifndef METADATAWINDOW_H
#define METADATAWINDOW_H

#include <QDialog>

class QAbstractItemModel;
class QListView;

namespace PowerLab {
namespace ModelResult {
  class ModelResult;
}
}

namespace PowerLab {
namespace Gui {

class MetaDataWindow : public QDialog {
public:
  explicit MetaDataWindow(QWidget *parent = nullptr);

  QAbstractItemModel* loadModelResults(const ModelResult::ModelResult& modelResult);

private:
  constexpr static size_t MIN_WINDOW_WIDTH = 500;
  constexpr static size_t MIN_WINDOW_HEIGHT = 400;
  QAbstractItemModel *m_signalsModel = nullptr;
  QAbstractItemModel *m_graphModel = nullptr;
  QListView *m_signalsView = nullptr;
  QListView *m_graphView = nullptr;

private slots:
  void addSignalToGraph();
  void removeSignalFromGraph();
};

} // namespace Gui
} // namespace PowerLab

#endif // METADATAWINDOW_H
