#include <QGraphicsScene>
#include <QGraphicsItem>

#include "modelwidget.h"
#include "modeldesign/elements/basic/resistor.h"
#include "modeldesign/elements/basic/capacitor.h"
#include "modeldesign/elements/basic/inductor.h"
#include "logger.h"

namespace PowerLab {
namespace Gui {

ModelWidget::ModelWidget(QWidget *parent, const QString& title)
  : QWidget(parent)
  , m_scene(new QGraphicsScene(this))
{
  setToolTip(tr("Model Design"));
  setWindowTitle(title);

  std::vector<ModelDesign::CircuitElement*> elements;
  elements.push_back(new ModelDesign::Resistor("R1"));
  elements.push_back(new ModelDesign::Inductor("L1"));
  elements.push_back(new ModelDesign::Capacitor("C1"));

  for(auto item : elements) {
    auto params = item->getAllParameters();
    Logger::log(Logger::Message::DEBUG_MSG, item->getName());
    for(auto p : params) {
      std::string desc = parameterTypeToStr(p->getType()) + ": " + std::to_string(p->getValue<double>()) + " " + p->getUnits();
      Logger::log(Logger::Message::DEBUG_MSG, desc);
    }
  }
}

} // namespace Gui
} // namespace PowerLab
