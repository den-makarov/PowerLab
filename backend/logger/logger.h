#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <map>
#include <set>
#include <functional>

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
    EMPTY
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
  Tag m_tag = Tag::EMPTY;
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

  bool operator()(const LogMessage& msg) const;

private:
  std::set<LogMessage::Tag> m_tagFilters;
  std::set<LogMessage::Severity> m_severityFilters;
  Operation m_operation;
};

class LogProvider {
public:
  using LogStreamId = int64_t;

  static LogProvider& instance() {
    static LogProvider logger;
    return logger;
  }

  void transmitMessage(const LogMessage& msg);

  LogStreamId addStream(std::ostream& stream);
  void removeStream(LogStreamId id);

  void addFilterToStream(LogStreamId id, LogMessageFilter filter);
  void removeFilterFromStream(LogStreamId id);

private:
  LogProvider() = default;
  std::map<LogStreamId, std::reference_wrapper<std::ostream>> m_logStreams;
  std::map<LogStreamId, LogMessageFilter> m_filters;
};

std::ostream& operator<<(std::ostream& out, const LogMessage& msg);
void LogSendMessage(const LogMessage& msg);

#endif // LOGGER_H
