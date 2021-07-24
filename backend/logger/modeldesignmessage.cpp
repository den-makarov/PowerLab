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
  };

  return msgPhrases.at(msg);
}

} // namespace ModelDesign
} // namespace PowerLab
