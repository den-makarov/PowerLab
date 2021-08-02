#include <map>

#include "modeldesignmessage.h"

namespace PowerLab {
namespace ModelDesign {

std::string getMessagePhrase(Message msg) {
  static std::map<Message, std::string> msgPhrases = {
    {Message::DEBUG_LAST, "Restricted to use"},
    {Message::INFO_LAST, "Restricted to use"},
    {Message::WARNING_LAST, "Restricted to use"},
    {Message::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    // Info messages
    // Warning messages
    // Error messages
    {Message::ERROR_ELEMENT_PARAMETER_DOESNT_SUPPORT_TYPE, "Wrong usage of parameter \"%1%\". It isn't %2% type"},
    {Message::ERROR_INVALID_CONNECTION, "Invalid connection Id: %1%"},
  };

  return msgPhrases.at(msg);
}

} // namespace ModelDesign
} // namespace PowerLab
