#include <map>

#include "system_message.h"

namespace PowerLab {
namespace System {

std::string getMessagePhrase(SystemMessage msg) {
  static std::map<SystemMessage, std::string> msgPhrases = {
    {SystemMessage::DEBUG_APPLICATION_START, "Hello %1%"},
    {SystemMessage::DEBUG_LAST, "Restricted to use"},
    {SystemMessage::INFO_LAST, "Restricted to use"},
    {SystemMessage::WARNING_LAST, "Restricted to use"},
    {SystemMessage::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    // Info messages
    // Warning messages
    {SystemMessage::WARNING_ATTEMPT_OPEN_UNKNOWN_FILE_FORMAT, "Attempt to open file with unsupported format. Filename: %1%"},
    // Error messages
  };

  return msgPhrases.at(msg);
}

} // namespace System
} // namespace PowerLab
