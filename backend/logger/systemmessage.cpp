#include <map>

#include "systemmessage.h"

namespace PowerLab {
namespace System {

std::string getMessagePhrase(Message msg) {
  static std::map<Message, std::string> msgPhrases = {
    {Message::DEBUG_APPLICATION_START, "Hello %1%"},
    {Message::DEBUG_LAST, "Restricted to use"},
    {Message::INFO_LAST, "Restricted to use"},
    {Message::WARNING_LAST, "Restricted to use"},
    {Message::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    // Info messages
    // Warning messages
    {Message::WARNING_ATTEMPT_OPEN_UNKNOWN_FILE_FORMAT, "Attempt to open file with unsupported format. Filename: %1%"},
    // Error messages
  };

  return msgPhrases.at(msg);
}

} // namespace System
} // namespace PowerLab
