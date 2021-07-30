#ifndef MODEL_DESIGN_MESSAGE_H
#define MODEL_DESIGN_MESSAGE_H

#include <string>

namespace PowerLab {
namespace ModelDesign {

enum class Message {
  // DEBUG MESSAGES
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_ELEMENT_PARAMETER_DOESNT_SUPPORT_TYPE,
  ERROR_LAST
};

std::string getMessagePhrase(Message msg);

} // namespace ModelDesign
} // namespace PowerLab

#endif // MODEL_DESIGN_MESSAGE_H
