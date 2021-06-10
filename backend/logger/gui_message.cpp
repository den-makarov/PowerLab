#include <map>

#include "gui_message.h"

namespace Gui {

std::string getMessagePhrase(GuiMessage msg) {
  static std::map<GuiMessage, std::string> msgPhrases = {
    {GuiMessage::DEBUG_LAST, "Restricted to use"},
    {GuiMessage::INFO_LAST, "Restricted to use"},
    {GuiMessage::WARNING_LAST, "Restricted to use"},
    {GuiMessage::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    {GuiMessage::DEBUG_ATTEMPT_ADD_ITEM_TWICE, "Attempt to add item that is already exists: %1%"},
    // Info messages
    // Warning messages
    // Error messages
    {GuiMessage::ERROR_SELECTION_INVALID, "Valid selection is expected"},
    {GuiMessage::ERROR_NO_META_DATA, "Meta data is expected"},
  };

  return msgPhrases.at(msg);
}

} // namespace Gui
