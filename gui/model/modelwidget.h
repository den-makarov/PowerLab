#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>

class ModelWidget : public QWidget {
  Q_OBJECT
public:
  explicit ModelWidget(QWidget *parent = nullptr, const QString& title = "untitled");

signals:

};

#endif // MODELWIDGET_H
