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
    // Info messages
    // Warning messages
    // Error messages
  };

  return msgPhrases.at(msg);
}

} // namespace Gui
