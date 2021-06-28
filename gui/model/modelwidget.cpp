#include "modelwidget.h"

ModelWidget::ModelWidget(QWidget *parent, const QString& title) : QWidget(parent) {
  setToolTip(tr("Model Design"));
  setWindowTitle(title);
}
