#include <map>

#include "guimessage.h"

namespace PowerLab {
namespace Gui {

std::string getMessagePhrase(Message msg) {
  static std::map<Message, std::string> msgPhrases = {
    {Message::DEBUG_LAST, "Restricted to use"},
    {Message::INFO_LAST, "Restricted to use"},
    {Message::WARNING_LAST, "Restricted to use"},
    {Message::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    {Message::DEBUG_ATTEMPT_ADD_ITEM_TWICE, "Attempt to add item that is already exists: %1%"},
    // Info messages
    // Warning messages
    {Message::WARNING_FORBIDDEN_LINE_WIDTH, "Forbidden line width %1%. Chose from range [%2%, %3%]"},
    {Message::WARNING_SET_PLOT_GRID_LINES_ON_AUTO_GRID, "Attempt to overwrite number of grid lines when auto grid lines mode is enabled. New grid lines values are ignored"},
    // Error messages
    {Message::ERROR_SELECTION_INVALID, "Valid selection is expected"},
    {Message::ERROR_NO_META_DATA, "Meta data is expected"},
    {Message::ERROR_ATTEMPT_PLOT_SAME_SIGNAL, "Attempt to add signal to graph that already has signal with similar name %1%"},
    {Message::ERROR_NO_DATA_TO_PLOT, "No data to plot graphs"},
    {Message::ERROR_NO_SELECTED_SIGNALS_TO_PLOT, "No signals were selected to plot"},
    {Message::ERROR_INVALID_NUMBER_OF_GRID_LINES, "Number %1% of grid lines isn't supported. Chose from range (%2%, %3%)"},
    {Message::ERROR_INVALID_GRAPH_INDEX, "Invalid graph index %1%"},
    {Message::ERROR_INVALID_GRAPH_SELECTOR_INDEX, "Invalid graph index selected %1%"},
    {Message::ERROR_INVALID_GRAPH_DATA_INDEX, "Invalid graph data index selected %1%. Expected range [0, %2%]"},
    {Message::ERROR_INVALID_GRAPH_SELECTOR_DATA, "Invalid associated data with selected graph. Current index %1%, selected text %2%"},
    {Message::ERROR_INVALID_COLOR, "Invalid color provided"},
    {Message::ERROR_INVALID_BUTTON_COLOR_CONTROL, "Invalid color control button"},
  };

  return msgPhrases.at(msg);
}

} // namespace Gui
} // namespace PowerLab
