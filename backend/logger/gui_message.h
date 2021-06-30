#ifndef GUI_MESSAGE_H
#define GUI_MESSAGE_H

#include <string>

namespace PowerLab {
namespace Gui {

enum class GuiMessage {
  // DEBUG MESSAGES
  DEBUG_ATTEMPT_ADD_ITEM_TWICE,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_SET_PLOT_GRID_LINES_ON_AUTO_GRID,
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_NO_META_DATA,
  ERROR_SELECTION_INVALID,
  ERROR_ATTEMPT_PLOT_SAME_SIGNAL,
  ERROR_NO_DATA_TO_PLOT,
  ERROR_NO_SELECTED_SIGNALS_TO_PLOT,
  ERROR_LAST
};

std::string getMessagePhrase(GuiMessage msg);

} // namespace Gui
} // namespace PowerLab

#endif // GUI_MESSAGE_H
