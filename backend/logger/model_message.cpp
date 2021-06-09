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
    {ModelMessage::DEBUG_NEW_MODEL_RESULT_STORAGE, "New storage for %1% variables and %2% points"},
    {ModelMessage::DEBUG_NEW_DATA_POINT_FOR_SIGNAL, "New data point for signal id %1%, point %2%"},
    {ModelMessage::DEBUG_NEW_DATA_FOR_SIGNAL, "New data for signal id %1%, point numbers %2%"},
    {ModelMessage::DEBUG_NO_FILE_SELECTED, "No file selected"},
    {ModelMessage::DEBUG_META_DATA_READY, "Meta data ready"},
    {ModelMessage::DEBUG_DEFAULT_META_DATA_CALLBACK, "Default meta-data parser used with message: %2%. Meta-data: %1%"},
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
    {ModelMessage::ERROR_INVALID_SIGNAL_ID, "Invalid signal id %1%"},
    {ModelMessage::ERROR_META_DATA_NOT_READY, "Unable to retrive meta data"},
  };

  return msgPhrases.at(msg);
}

} // namespace Model
