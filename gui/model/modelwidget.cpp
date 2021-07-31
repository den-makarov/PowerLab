#include <QGraphicsScene>
#include <QGraphicsItem>

#include "modelwidget.h"
#include "modeldesign/elements/basic/resistor.h"
#include "modeldesign/elements/basic/capacitor.h"
#include "modeldesign/elements/basic/inductor.h"
#include "modeldesign/elements/basic/switch.h"
#include "modeldesign/parameters/switchstate.h"
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
  elements.push_back(new ModelDesign::Switch("SW1"));

  for(auto item : elements) {
    auto params = item->getAllParameters();
    std::string desc = "Element " + item->getName();
    for(auto p : params) {
      std::string value;
      if(p->getType() == ModelDesign::ParameterType::STATE) {
        ModelDesign::SwitchState state(p->getValue<int>());
        value = state.str();
      } else {
        value = std::to_string(p->getValue<double>());
      }
      desc += " " + parameterTypeToStr(p->getType()) + ": " + value + " " + p->getUnits();
      Logger::log(Logger::Message::DEBUG_MSG, desc);
    }
  }
}

} // namespace Gui
} // namespace PowerLab
