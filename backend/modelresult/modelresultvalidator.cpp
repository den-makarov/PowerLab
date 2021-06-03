#include "modelresultvalidator.h"
#include "modelresultmeta.h"
#include "backend/logger/logger.h"

/**
 * @brief ModelResultValidator::ModelResultValidator
 * @param parent
 */
ModelResultValidator::ModelResultValidator()
  : m_meta(new ModelResultMeta())
{
// EMPTY
}

ModelResultValidator::~ModelResultValidator() {
  if(m_meta) {
    delete m_meta;
    m_meta = nullptr;
  }
}

/**
 * @brief ModelResultValidator::validate
 * @param filename
 * @return
 */
bool ModelResultValidator::validate(const std::string& filename) {
  bool result = false;

  if(filename.empty()) {
    Logger::log(Model::ModelMessage::ERROR_NO_FILENAME_TO_VALIDATE);
    return result;
  }

  std::ifstream file(filename);
  if(!file.is_open()) {
    Logger::log(Model::ModelMessage::ERROR_FILE_NOT_OPEN, filename);
    return result;
  }

  for(std::string line; std::getline(file, line); ) {
    auto token = m_meta->determineToken(line);

    if(token == ModelResultMeta::TokenType::UNKNOWN) {
      Logger::log(Model::ModelMessage::WARNING_UNKNOWN_META_DATA, line);
      break;
    } else if(token == ModelResultMeta::TokenType::SIGNALS) {
      if(readSignalLines(file, line)) {
        result = m_meta->addToken(ModelResultMeta::TokenType::SIGNALS, line);
      }
      // Expected end of meta data
      break;
    } else {
      // Any meta data type that is determined successfully
      if(!m_meta->addToken(token, line)) {
        Logger::log(Model::ModelMessage::ERROR_META_DATA_TOKEN_LOAD, token, line);
        break;
      }
    }
  }

  if(result) {
    m_meta->parseData();
  }

  Logger::log(Model::ModelMessage::DEBUG_META_DATA_PARSING_COMPLETE, m_meta->getData());

  return result;
}

/**
 * @brief ModelResultValidator::validateSignals
 * @param file
 * @param line
 * @return
 */
bool ModelResultValidator::readSignalLines(std::ifstream& file, std::string& line) {
  bool result = false;

  auto varNumberRef = m_meta->peekTokenData(ModelResultMeta::TokenType::VAR_COUNT);

  if(!varNumberRef.empty()) {
    auto num = std::stoi(varNumberRef.data());

    for(int i = 0; i < num; i++) {
      if(i >= MAX_COUNT_OF_SIGNALS) {
          Logger::log(Model::ModelMessage::WARNING_MAX_SIGNAL_NUMBER_LIMIT, MAX_COUNT_OF_SIGNALS);
        break;
      }

      if(!file.eof()) {
        std::string signal;
        std::getline(file, signal);
        line.append(signal);
      } else {
        Logger::log(Model::ModelMessage::ERROR_UNEXPECTED_FILE_END);
        return result;
      }
    }
    result = true;
  }

  return result;
}
