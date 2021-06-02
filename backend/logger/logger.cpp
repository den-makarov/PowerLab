#include "logger.h"

void LogSendMessage(const LogMessage& msg) {
  LogProvider::instance().transmitMessage(msg);
}

std::ostream& operator<<(std::ostream& out, const LogMessage& msg) {
  std::string tag;
  switch(msg.m_tag) {
    case LogMessage::Tag::EMPTY: tag = ""; break;
    case LogMessage::Tag::GUI: tag = "GUI"; break;
    case LogMessage::Tag::SYSTEM: tag = "SYSTEM"; break;
    case LogMessage::Tag::MODEL_RESULT: tag = "MODEL_RESULT"; break;
  }

  std::string severity;
  switch(msg.m_severity) {
    case LogMessage::Severity::DEBUG: severity = "DEBUG"; break;
    case LogMessage::Severity::INFO: severity = "INFO"; break;
    case LogMessage::Severity::WARNING: severity = "WARNING"; break;
    case LogMessage::Severity::ERROR: severity = "ERROR"; break;
  }

  out << "[" << severity << "] "
      << "<" << tag << "> "
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
