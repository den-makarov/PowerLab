#ifndef SYSTEM_MESSAGE_H
#define SYSTEM_MESSAGE_H

#include <string>

namespace PowerLab {
namespace System {

enum class SystemMessage {
  // DEBUG MESSAGES
  DEBUG_APPLICATION_START,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_ATTEMPT_OPEN_UNKNOWN_FILE_FORMAT,
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_LAST
};

std::string getMessagePhrase(SystemMessage msg);

} // namespace System
} // namespace PowerLab

#endif // SYSTEM_MESSAGE_H
