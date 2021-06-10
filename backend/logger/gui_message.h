#ifndef GUI_MESSAGE_H
#define GUI_MESSAGE_H

#include <string>

namespace Gui {

enum class GuiMessage {
  // DEBUG MESSAGES
  DEBUG_ATTEMPT_ADD_ITEM_TWICE,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_NO_META_DATA,
  ERROR_SELECTION_INVALID,
  ERROR_LAST
};

std::string getMessagePhrase(GuiMessage msg);

} // namespace Gui

#endif // GUI_MESSAGE_H
