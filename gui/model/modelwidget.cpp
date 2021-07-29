#include <QGraphicsScene>
#include <QGraphicsItem>

#include "modelwidget.h"
#include "modeldesign/elements/basic/resistor.h"
#include "logger.h"

namespace PowerLab {
namespace Gui {

ModelWidget::ModelWidget(QWidget *parent, const QString& title)
  : QWidget(parent)
  , m_scene(new QGraphicsScene(this))
{
  setToolTip(tr("Model Design"));
  setWindowTitle(title);
  ModelDesign::CircuitElement* R = new ModelDesign::Resistor("R1");
  Logger::log(Logger::Message::DEBUG_MSG, R->getName());
  auto value = R->getParameter(parameterTypeToString(ModelDesign::ParameterType::RESISTANCE));
  if(value) {
    std::string param = parameterTypeToString(value->getType()) + ": " + std::to_string(value->getValue<double>()) + " " + value->getUnits();
    Logger::log(Logger::Message::DEBUG_MSG, param);
  }
  delete R;
}

} // namespace Gui
} // namespace PowerLab
