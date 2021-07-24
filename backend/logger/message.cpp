#include <map>

#include "message.h"

namespace PowerLab {
namespace Logger {

std::ostream& operator<<(std::ostream& out, const LogMessage::Tag& tag) {
  switch(tag) {
    case LogMessage::Tag::NONE: out << "NONE"; break;
    case LogMessage::Tag::GUI: out << "GUI"; break;
    case LogMessage::Tag::SYSTEM: out << "SYSTEM"; break;
    case LogMessage::Tag::MODEL_RESULT: out << "MODEL_RESULT"; break;
    case LogMessage::Tag::MODEL_DESIGN: out << "MODEL_DESIGN"; break;
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

std::string getMessagePhrase(Message msg) {
  static std::map<Message, std::string> msgPhrases = {
    {Message::DEBUG_LAST, "Restricted to use"},
    {Message::INFO_LAST, "Restricted to use"},
    {Message::WARNING_LAST, "Restricted to use"},
    {Message::ERROR_LAST, "Restricted to use"},
    // Debug messagess
    {Message::DEBUG_MSG, "%1%"},
    // Info messages
    // Warning messages
    // Error messages
  };

  return msgPhrases.at(msg);
}

} // namespace Logger
} // namespace PowerLab
