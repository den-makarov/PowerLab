#include <map>

#include "modelresultmessage.h"

namespace PowerLab {
namespace ModelResult {

std::string getMessagePhrase(Message msg) {
  static std::map<Message, std::string> msgPhrases = {
    {Message::DEBUG_LAST, "Restricted to use"},
    {Message::INFO_LAST, "Restricted to use"},
    {Message::WARNING_LAST, "Restricted to use"},
    {Message::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    {Message::DEBUG_META_DATA_PARSING_COMPLETE, "Meta data parsed. %1%"},
    {Message::DEBUG_NEW_MODEL_RESULT_DATA, "ModelResult data with %1% variables and %2% points"},
    {Message::DEBUG_NEW_DATA_POINT_FOR_SIGNAL, "New data point for signal \"%1%\", point %2%"},
    {Message::DEBUG_NEW_DATA_FOR_SIGNAL, "New data for signal \"%1%\", number of points %2%"},
    {Message::DEBUG_NO_FILE_SELECTED, "No file selected"},
    {Message::DEBUG_META_DATA_READY, "Meta data ready"},
    {Message::DEBUG_DEFAULT_META_DATA_CALLBACK, "Default meta-data parser used with message: %1%, %2%"},
    {Message::DEBUG_VALUES_FILE_EXPECTED_END_REACHED, "All values are exctracted successfully"},
    // Info messages
    // Warning messages
    {Message::WARNING_UNKNOWN_META_DATA, "Attempt to parse unsupported meta data: %1%"},
    {ModelResult::Message::WARNING_MAX_SIGNAL_NUMBER_LIMIT, "Limit of signals reached: %1%"},
    // Error messages
    {Message::ERROR_NO_FILENAME_TO_VALIDATE, "No filename is provided to validate"},
    {Message::ERROR_META_DATA_FILE_NOT_OPEN, "Open file with meta data \"%1%\" failed. Check file location"},
    {Message::ERROR_VALUES_FILE_NOT_OPEN, "Open file with values \"%1%\" failed. Check file location"},
    {Message::ERROR_META_DATA_TOKEN_LOAD, "Error while adding token: %1% from line: %2%"},
    {Message::ERROR_ADD_UNKNOWN_TOKEN, "Attempt to add unknown token with context: %1%"},
    {Message::ERROR_UNEXPECTED_FILE_END, "Unexpected file end"},
    {Message::ERROR_UNKNOWN_SIGNAL_NAME, "Unknown signal name \"%1%\""},
    {Message::ERROR_META_DATA_NOT_READY, "Unable to retrive meta data"},
    {Message::ERROR_VALUES_NOT_FOUND, "No \"Values:\" section in model result data file is found. Check file format. Filename %1%"},
    {Message::ERROR_DATA_POINT_INDEX_INVALID, "Data point index %1% is greater than total number of data points: %2%"},
    {Message::ERROR_VALUES_UNEXPECTED_END, "Unexpected end of the file with values. Expected signals %1% and data points %2%, but parsed only %3% points"},
  };

  return msgPhrases.at(msg);
}

} // namespace ModelResult
} // namespace PowerLab
