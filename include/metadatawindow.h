#ifndef METADATAWINDOW_H
#define METADATAWINDOW_H

#include <QDialog>

class MetaDataWindow : public QDialog
{
  Q_OBJECT
public:
  explicit MetaDataWindow(QWidget *parent = nullptr);
  virtual ~MetaDataWindow() {}

signals:

private:
  constexpr static size_t MIN_WINDOW_WIDTH = 500;
  constexpr static size_t MIN_WINDOW_HEIGHT = 400;
};

#endif // METADATAWINDOW_H
