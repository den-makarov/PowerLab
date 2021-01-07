#ifndef METADATAWINDOW_H
#define METADATAWINDOW_H

#include <QDialog>

#include "modelresultmeta.h"

class QAbstractItemModel;

class MetaDataWindow : public QDialog
{
  Q_OBJECT
public:
  explicit MetaDataWindow(QWidget *parent = nullptr);
  virtual ~MetaDataWindow() {}
  void loadModelResults(const ModelResultMeta::Data* data);

signals:

private:
  constexpr static size_t MIN_WINDOW_WIDTH = 500;
  constexpr static size_t MIN_WINDOW_HEIGHT = 400;
  QAbstractItemModel *signals_model = nullptr;
  QAbstractItemModel *graph_model = nullptr;
};

#endif // METADATAWINDOW_H
