#include <map>

#include "message.h"

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

std::string getMessagePhrase(DefaultMessage msg) {
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

  return msgPhrases.at(msg);
}

} // namespace Logger
