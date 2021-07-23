#include <QPlainTextEdit>
#include <QDockWidget>

#include "mainwindow/mainwindow.h"
#include "model/modelwidget.h"

namespace PowerLab {
namespace Gui {

void MainWindow::addDefaultModelDesignWidget() {
  auto widget = new ModelWidget(this);
//  createDockWindow(widget, WidgetType::MODEL_DESIGN, "Untitled");
  setCentralWidget(widget);

  m_logOutput = new QPlainTextEdit(this);
  createDockWindow(m_logOutput, WidgetType::MODEL_DESIGN, "Logger");
  m_logOutput->setReadOnly(true);
  m_logOutput->appendPlainText("Logger started\n");
  m_logOutput->setCenterOnScroll(true);
  connect(m_logOutput, &QPlainTextEdit::destroyed, [this](){
    this->m_logOutput = nullptr;
  });
}

void MainWindow::debugMsg(std::string str) {
  if(m_logOutput) {
    m_logOutput->appendPlainText(QString::fromStdString(str));
  }
}

} // namespace Gui
} // namespace PowerLab
