#include <QDockWidget>

#include "mainwindow/mainwindow.h"
#include "library/librarywidget.h"

namespace PowerLab {
namespace Gui {

bool MainWindow::createLibraryWidgets() {
  bool result = true;

  m_library = new LibraryWidget(this);

//  connect(this, &MainWindow::newModelDesignWidget, [library](QWidget*){
//    library->update();
//  });

  if(!createDockWindow(m_library, WidgetType::LIBRARY, tr("Library"))) {
    result = false;
  }

  return result;
}

void MainWindow::showLibrary() {
  // @TODO: Check what widget type is in focus
//  library->update();
  for(auto dock : m_docksList) {
    if(dock->windowTitle() == tr("Library")) {
      if(dock->isHidden()) {
        dock->setHidden(false);
      } else {
        dock->setHidden(true);
      }
    }
  }
}

} // namespace Gui
} // namespace PowerLab
