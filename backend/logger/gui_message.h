#ifndef GUI_MESSAGE_H
#define GUI_MESSAGE_H

#include <string>

namespace Gui {
enum class GuiMessage {
  // DEBUG MESSAGES
  DEBUG_GUI_START,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_LAST
};

std::string getMessagePhrase(GuiMessage msg);

} // namespace Gui

#endif // GUI_MESSAGE_H
