#include <map>

#include "gui_message.h"

namespace PowerLab {
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
    {GuiMessage::WARNING_FORBIDDEN_LINE_WIDTH, "Forbidden line width %1%. Chose from range [%2%, %3%]"},
    {GuiMessage::WARNING_SET_PLOT_GRID_LINES_ON_AUTO_GRID, "Attempt to overwrite number of grid lines when auto grid lines mode is enabled. New grid lines values are ignored"},
    // Error messages
    {GuiMessage::ERROR_SELECTION_INVALID, "Valid selection is expected"},
    {GuiMessage::ERROR_NO_META_DATA, "Meta data is expected"},
    {GuiMessage::ERROR_ATTEMPT_PLOT_SAME_SIGNAL, "Attempt to add signal to graph that already has signal with similar name %1%"},
    {GuiMessage::ERROR_NO_DATA_TO_PLOT, "No data to plot graphs"},
    {GuiMessage::ERROR_NO_SELECTED_SIGNALS_TO_PLOT, "No signals were selected to plot"},
    {GuiMessage::ERROR_INVALID_NUMBER_OF_GRID_LINES, "Number %1% of grid lines isn't supported. Chose from range (%2%, %3%)"},
    {GuiMessage::ERROR_INVALID_GRAPH_INDEX, "Invalid graph index %1%"},
  };

  return msgPhrases.at(msg);
}

} // namespace Gui
} // namespace PowerLab
