#ifndef SYSTEM_MESSAGE_H
#define SYSTEM_MESSAGE_H

#include <string>

namespace System {

enum class SystemMessage {
  // DEBUG MESSAGES
  DEBUG_APPLICATION_START,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_LAST
};

std::string getMessagePhrase(SystemMessage msg);

} // namespace System

#endif // SYSTEM_MESSAGE_H
