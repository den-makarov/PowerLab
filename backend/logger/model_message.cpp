#include <map>

#include "model_message.h"

namespace Model {

std::string getMessagePhrase(ModelMessage msg) {
  static std::map<ModelMessage, std::string> msgPhrases = {
    {ModelMessage::DEBUG_LAST, "Restricted to use"},
    {ModelMessage::INFO_LAST, "Restricted to use"},
    {ModelMessage::WARNING_LAST, "Restricted to use"},
    {ModelMessage::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    {ModelMessage::DEBUG_META_DATA_PARSING_COMPLETE, "Meta data parsed. %1%"},
    // Info messages
    // Warning messages
    {ModelMessage::WARNING_UNKNOWN_META_DATA, "Attempt to parse unsupported meta data: %1%"},
    {Model::ModelMessage::WARNING_MAX_SIGNAL_NUMBER_LIMIT, "Limit of signals reached: %1%"},
    // Error messages
    {ModelMessage::ERROR_NO_FILENAME_TO_VALIDATE, "No filename is provided to validate"},
    {ModelMessage::ERROR_FILE_NOT_OPEN, "Open file \"%1%\" failed. Check file location"},
    {ModelMessage::ERROR_META_DATA_TOKEN_LOAD, "Error while adding token: %1% from line: %2%"},
    {ModelMessage::ERROR_ADD_UNKNOWN_TOKEN, "Attempt to add unknown token with context: %1%"},
    {ModelMessage::ERROR_UNEXPECTED_FILE_END, "Unexpected file end"},
  };

  return msgPhrases.at(msg);
}

} // namespace Model
