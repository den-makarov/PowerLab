#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <functional>
#include <set>

namespace PowerLab {
namespace Logger {

enum class Message {
  // DEBUG MESSAGES
  DEBUG_MSG,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_LAST
};

class LogMessage {
public:
  enum class Severity {
    DEBUG,
    INFO,
    WARNING,
    ERROR
  };

  enum class Tag {
    SYSTEM,
    GUI,
    MODEL_RESULT,
    MODEL_DESIGN,
    NONE
  };

  explicit LogMessage(Tag tag, std::string&& text, Severity severity = Severity::DEBUG)
    : m_tag(tag)
    , m_msgText(std::move(text))
    , m_severity(severity)
  {
  }

  Severity getSeverity() const {
    return m_severity;
  }

  Tag getTag() const {
    return m_tag;
  }

  friend std::ostream& operator<<(std::ostream& out, const LogMessage& msg);
private:
  Tag m_tag = Tag::NONE;
  std::string m_msgText;
  Severity m_severity;
};

class LogMessageFilter {
public:
  enum class Operation {
    CONJUCTION_FILTER,
    DISJUCTION_FILTER,
    CONJUCTION_PASS,
    DISJUCTION_PASS,
  };

  template<typename TagsSet, typename SeveritySet>
  LogMessageFilter(TagsSet tags,
                   SeveritySet severities,
                   Operation operation = Operation::CONJUCTION_FILTER)
    : m_tagFilters(std::move(tags))
    , m_severityFilters(std::move(severities))
    , m_operation(operation)
  {
  }

  explicit LogMessageFilter(LogMessage::Tag tag,
                            LogMessage::Severity severity,
                            Operation operation = Operation::CONJUCTION_FILTER)
    : m_operation(operation)
  {
    m_tagFilters.insert(tag);
    m_severityFilters.insert(severity);
  }

  void setUserCb(std::function<void(const LogMessage& msg, bool filter)> userCb) {
    m_userCb = userCb;
  }

  bool operator()(const LogMessage& msg) const;

private:
  std::set<LogMessage::Tag> m_tagFilters;
  std::set<LogMessage::Severity> m_severityFilters;
  Operation m_operation;
  std::function<void(const LogMessage&, bool)> m_userCb;
};

std::ostream& operator<<(std::ostream& out, const LogMessage& msg);
std::string getMessagePhrase(Message msg);

} // namespace Logger
} // namespace PowerLab

#endif // MESSAGE_H
