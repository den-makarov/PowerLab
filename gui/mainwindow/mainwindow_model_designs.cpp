#include <QPlainTextEdit>

#include "mainwindow/mainwindow.h"
#include "model/modelwidget.h"

namespace PowerLab {
namespace Gui {

void MainWindow::addDefaultModelDesignWidget() {
//  auto widget = new ModelWidget(this);
//  widget->setWindowModified(true);
  m_logOutput = new QPlainTextEdit(this);
  m_logOutput->setReadOnly(true);
  setCentralWidget(m_logOutput);
  m_logOutput->appendPlainText("Logger started\n");
  m_logOutput->setCenterOnScroll(true);
  connect(m_logOutput, &QPlainTextEdit::destroyed, [this](){
    this->m_logOutput = nullptr;
  });
  //  createDockWindow(widget, WidgetType::MODEL_DESIGN, "Untitled");
}

void MainWindow::debugMsg(std::string str) {
  if(m_logOutput) {
    m_logOutput->appendPlainText(QString::fromStdString(str));
  }
}

} // namespace Gui
} // namespace PowerLab
