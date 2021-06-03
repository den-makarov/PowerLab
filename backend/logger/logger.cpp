#include "logger.h"

namespace Logger {

std::ostream& operator<<(std::ostream& out, const LogMessage::Tag& tag) {
  switch(tag) {
    case LogMessage::Tag::NONE: break;
    case LogMessage::Tag::GUI: out << "GUI"; break;
    case LogMessage::Tag::SYSTEM: out << "SYSTEM"; break;
    case LogMessage::Tag::MODEL_RESULT: out << "MODEL_RESULT"; break;
  }

  return out;
}

std::ostream& operator<<(std::ostream& out, const LogMessage::Severity& severity) {
  switch(severity) {
    case LogMessage::Severity::DEBUG: out << "DEBUG"; break;
    case LogMessage::Severity::INFO: out << "INFO"; break;
    case LogMessage::Severity::WARNING: out << "WARNING"; break;
    case LogMessage::Severity::ERROR: out << "ERROR"; break;
  }

  return out;
}

std::ostream& operator<<(std::ostream& out, const LogMessage& msg) {
  out << "[" << msg.getSeverity() << "] "
      << "<" << msg.getTag() << "> "
      << msg.m_msgText << std::endl;

  return out;
}

bool LogMessageFilter::operator()(const LogMessage& msg) const {
  bool tagFound = m_tagFilters.find(msg.getTag()) != m_tagFilters.end();
  bool severityFound = m_severityFilters.find(msg.getSeverity()) != m_severityFilters.end();

  bool result = false;
  switch(m_operation) {
    case Operation::CONJUCTION_FILTER: result = !(tagFound && severityFound); break;
    case Operation::DISJUCTION_FILTER: result = !(tagFound || severityFound); break;
    case Operation::CONJUCTION_PASS: result = tagFound && severityFound; break;
    case Operation::DISJUCTION_PASS: result = tagFound || severityFound; break;
  }

  if(m_userCb) {
    m_userCb(msg, result);
  }

  return result;
}

void LogProvider::transmitMessage(const LogMessage& msg) {
  for(auto [id, stream] : m_logStreams) {
    auto filter_it = m_filters.find(id);
    if(filter_it != m_filters.end()) {
      auto& filter = filter_it->second;
      if(filter(msg)) {
        stream << msg;
      }
    } else {
      stream << msg;
    }
  }
}

LogProvider::LogStreamId LogProvider::addStream(std::ostream& stream) {
  LogStreamId id = 0;

  if(m_logStreams.empty()) {
    m_logStreams.emplace(id, stream);
  } else {
    id = m_logStreams.rbegin()->first + 1;
    m_logStreams.emplace(id, stream);
  }

  return id;
}

void LogProvider::addFilterToStream(LogProvider::LogStreamId id, LogMessageFilter filter) {
  if(m_logStreams.count(id)) {
    m_filters.emplace(id, filter);
  }
}

void LogProvider::removeStream(LogProvider::LogStreamId id) {
  if(m_logStreams.count(id)) {
    m_logStreams.erase(id);
    removeFilterFromStream(id);
  }
}

void LogProvider::removeFilterFromStream(LogProvider::LogStreamId id) {
  if(m_filters.count(id)) {
    m_filters.erase(id);
  }
}

std::string LogProvider::getPhrase(System::SystemMessage msgType) const {
  static std::map<System::SystemMessage, std::string> msgPhrases = {
    {System::SystemMessage::DEBUG_APPLICATION_START, "Hello %1%"},
    {System::SystemMessage::DEBUG_LAST, "Restricted to use"},
    {System::SystemMessage::INFO_LAST, "Restricted to use"},
    {System::SystemMessage::WARNING_LAST, "Restricted to use"},
    {System::SystemMessage::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    // Info messages
    // Warning messages
    // Error messages
  };

  return msgPhrases.at(msgType);
}

std::string LogProvider::getPhrase(Gui::GuiMessage msgType) const {
  static std::map<Gui::GuiMessage, std::string> msgPhrases = {
    {Gui::GuiMessage::DEBUG_LAST, "Restricted to use"},
    {Gui::GuiMessage::INFO_LAST, "Restricted to use"},
    {Gui::GuiMessage::WARNING_LAST, "Restricted to use"},
    {Gui::GuiMessage::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    // Info messages
    // Warning messages
    // Error messages
  };

  return msgPhrases.at(msgType);
}

std::string LogProvider::getPhrase(Model::ModelMessage msgType) const {
  static std::map<Model::ModelMessage, std::string> msgPhrases = {
    {Model::ModelMessage::DEBUG_LAST, "Restricted to use"},
    {Model::ModelMessage::INFO_LAST, "Restricted to use"},
    {Model::ModelMessage::WARNING_LAST, "Restricted to use"},
    {Model::ModelMessage::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    {Model::ModelMessage::DEBUG_META_DATA_PARSING_COMPLETE, "Meta data parsed. %1%"},
    // Info messages
    // Warning messages
    {Model::ModelMessage::WARNING_UNKNOWN_META_DATA, "Attempt to parse unsupported meta data: %1%"},
    {Model::ModelMessage::WARNING_MAX_SIGNAL_NUMBER_LIMIT, "Limit of signals reached: %1%"},
    // Error messages
    {Model::ModelMessage::ERROR_NO_FILENAME_TO_VALIDATE, "No filename is provided to validate"},
    {Model::ModelMessage::ERROR_FILE_NOT_OPEN, "Open file \"%1%\" failed. Check file location"},
    {Model::ModelMessage::ERROR_META_DATA_TOKEN_LOAD, "Error while adding token: %1% from line: %2%"},
    {Model::ModelMessage::ERROR_ADD_UNKNOWN_TOKEN, "Attempt to add unknown token with context: %1%"},
    {Model::ModelMessage::ERROR_UNEXPECTED_FILE_END, "Unexpected file end"},
  };

  return msgPhrases.at(msgType);
}

std::string LogProvider::getPhrase(DefaultMessage msgType) const {
  static std::map<DefaultMessage, std::string> msgPhrases = {
    {DefaultMessage::DEBUG_LAST, "Restricted to use"},
    {DefaultMessage::INFO_LAST, "Restricted to use"},
    {DefaultMessage::WARNING_LAST, "Restricted to use"},
    {DefaultMessage::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    // Info messages
    // Warning messages
    // Error messages
  };

  return msgPhrases.at(msgType);
}

} // namespace Logger
