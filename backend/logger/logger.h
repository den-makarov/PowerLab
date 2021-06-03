#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <functional>
#include <vector>
#include <cctype>
#include <limits>

namespace System {
enum class SystemMessage {
  // DEBUG MESSAGES
  DEBUG_APPLICATION_START,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_LAST
};
} // namespace System

namespace Gui {
enum class GuiMessage {
  // DEBUG MESSAGES
  DEBUG_GUI_START,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_LAST
};
} // namespace Gui

namespace Model {
enum class ModelMessage {
  // DEBUG MESSAGES
  DEBUG_META_DATA_PARSING_COMPLETE,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_UNKNOWN_META_DATA,
  WARNING_MAX_SIGNAL_NUMBER_LIMIT,
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_NO_FILENAME_TO_VALIDATE,
  ERROR_FILE_NOT_OPEN,
  ERROR_ADD_UNKNOWN_TOKEN,
  ERROR_META_DATA_TOKEN_LOAD,
  ERROR_UNEXPECTED_FILE_END,
  ERROR_LAST
};
} // namespace Model

enum class DefaultMessage {
  // DEBUG MESSAGES
  DEBUG_DEFAULT,
  DEBUG_LAST,

  // INFO MESSAGES
  INFO_LAST,

  // WARNING MESSAGES
  WARNING_LAST,

  // ERROR MESSAGES
  ERROR_LAST
};

namespace Logger {

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

class LogProvider {
public:
  using LogStreamId = int64_t;

  static LogProvider& instance() {
    static LogProvider logger;
    return logger;
  }

  template<typename T, typename... Args>
  void sendMessage(T msgType, Args... args) {
    auto phrase = getPhrase(msgType);
    auto msgText = formatText(phrase, args...);
    auto tag = msgTypeToTag(msgType);
    auto severity = extractSeverity(msgType);
    LogMessage msg(tag, std::move(msgText), severity);
    LogProvider::instance().transmitMessage(msg);
  }

  void transmitMessage(const LogMessage& msg);

  LogStreamId addStream(std::ostream& stream);
  void removeStream(LogStreamId id);

  void addFilterToStream(LogStreamId id, LogMessageFilter filter);
  void removeFilterFromStream(LogStreamId id);
private:
  LogProvider() = default;

  using PlacersFmt = std::vector<std::pair<size_t, size_t>>;

  template<typename T>
  std::string substitutePlacers(const std::string& str, size_t pos, size_t size, T arg) const {
    std::ostringstream result;
    result << str.substr(0, pos) << arg << str.substr(pos + size);
    return result.str();
  }

  PlacersFmt searchForPlacers(const std::string& format) const {
    LogProvider::PlacersFmt placers;
    int minPlacer = std::numeric_limits<int>::max();
    for(int j = static_cast<int>(format.size()) - 3; j >= 0; j--) {
      size_t i = static_cast<size_t>(j);
      if(format[i] == '%' && std::isdigit(format[i + 1])) {
        size_t cnt = 0;
        int placer = stoi(format.substr(i + 1), &cnt);
        if(cnt != 0 && format[i + cnt + 1] == '%') {
          if(placer < minPlacer) {
            placers = PlacersFmt(1, {i, cnt + 2});
            minPlacer = placer;
          } else if(placer == minPlacer) {
            placers.emplace_back(i, cnt + 2);
          }
        }
      }
    }

    return placers;
  }

  std::string formatText(const std::string& format) const {
    return format;
  }

  template<typename T>
  std::string formatText(const std::string& format, T arg) const {
    std::string out = format;
    auto placers = searchForPlacers(out);
    for(auto item : placers) {
      out = substitutePlacers(out, item.first, item.second, arg);
    }
    return out;
  }

  template<typename T, typename... Args>
  std::string formatText(const std::string& format, T firstArg, Args... args) const {
    std::string out;
    if(sizeof...(args) != 0) {
      out = formatText(format, firstArg);
      out = formatText(out, args...);
    } else {
      out = format;
    }

    return out;
  }

  std::string getPhrase(System::SystemMessage msgType) const;
  std::string getPhrase(Gui::GuiMessage msgType) const;
  std::string getPhrase(Model::ModelMessage msgType) const;
  std::string getPhrase(DefaultMessage msgType) const;

  LogMessage::Tag msgTypeToTag(System::SystemMessage) const { return LogMessage::Tag::SYSTEM; }
  LogMessage::Tag msgTypeToTag(Gui::GuiMessage) const { return LogMessage::Tag::GUI; }
  LogMessage::Tag msgTypeToTag(Model::ModelMessage) const { return LogMessage::Tag::MODEL_RESULT; }
  LogMessage::Tag msgTypeToTag(DefaultMessage) const { return LogMessage::Tag::NONE; }

  template<typename Enum>
  LogMessage::Severity extractSeverity(Enum value) const {
    LogMessage::Severity severity = LogMessage::Severity::ERROR;
    static_assert(Enum::DEBUG_LAST != Enum::INFO_LAST, "Enum declaration invalid");
    static_assert(Enum::INFO_LAST != Enum::WARNING_LAST, "Enum declaration invalid");
    static_assert(Enum::WARNING_LAST != Enum::ERROR_LAST, "Enum declaration invalid");

    if(value < Enum::DEBUG_LAST) {
      severity = LogMessage::Severity::DEBUG;
    } else if(value < Enum::INFO_LAST) {
      severity = LogMessage::Severity::INFO;
    } else if(value < Enum::WARNING_LAST) {
      severity = LogMessage::Severity::WARNING;
    }

    return severity;
  }

  std::map<LogStreamId, std::reference_wrapper<std::ostream>> m_logStreams;
  std::map<LogStreamId, LogMessageFilter> m_filters;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
  out << "vector content: {";
  for(size_t i = 0; i + 1 < v.size(); i++) {
    out << v[i] << ", ";
  }

  if(!v.empty()) {
    out << v.back();
  }
  out << "}";

  return out;
}

std::ostream& operator<<(std::ostream& out, const LogMessage& msg);

template<typename T, typename... Args>
void log(T msgType, Args... args) {
  LogProvider::instance().sendMessage(msgType, args...);
}

} // namespace Logger
#endif // LOGGER_H
