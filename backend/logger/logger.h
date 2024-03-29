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
#include <type_traits>

#include "message.h"
#include "systemmessage.h"
#include "modelresultmessage.h"
#include "modeldesignmessage.h"
#include "guimessage.h"

namespace PowerLab {
namespace Logger {

class LogStreamHunter {
public:
  using UserCallBack = std::function<void(std::string)>;
  explicit LogStreamHunter(UserCallBack cb)
    : m_userCB(cb)
  {}

  void operator<<(const LogMessage& msg) {
    std::ostringstream out;
    out << msg;

    if(m_userCB) {
      m_userCB(out.str());
    }
  }
private:
  std::function<void(std::string)> m_userCB;
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
  void addStreamHunter(LogStreamHunter hunter);
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

  template<typename T>
  std::string getPhrase(T msgType) {
    using namespace Gui;
    using namespace System;
    using namespace ModelResult;
    using namespace ModelDesign;
    return getMessagePhrase(msgType);
  }

  template<typename Enum>
  LogMessage::Severity extractSeverity(Enum value) const {
    static_assert(Enum::DEBUG_LAST != Enum::INFO_LAST, "Enum declaration invalid");
    static_assert(Enum::INFO_LAST != Enum::WARNING_LAST, "Enum declaration invalid");
    static_assert(Enum::WARNING_LAST != Enum::ERROR_LAST, "Enum declaration invalid");

    LogMessage::Severity severity = LogMessage::Severity::ERROR;

    if(value < Enum::DEBUG_LAST) {
      severity = LogMessage::Severity::DEBUG;
    } else if(value < Enum::INFO_LAST) {
      severity = LogMessage::Severity::INFO;
    } else if(value < Enum::WARNING_LAST) {
      severity = LogMessage::Severity::WARNING;
    }

    return severity;
  }

  PlacersFmt searchForPlacers(const std::string& format) const;

  // Workaround: https://en.cppreference.com/w/cpp/language/if
  template<typename T> struct dependent_false : std::false_type {};

  template<typename T>
  LogMessage::Tag msgTypeToTag(T /* msgType*/ ) const {
    if constexpr(std::is_same<T, System::Message>::value) {
      return LogMessage::Tag::SYSTEM;
    } else if constexpr(std::is_same<T, Gui::Message>::value) {
      return LogMessage::Tag::GUI;
    } else if constexpr(std::is_same<T, ModelResult::Message>::value) {
      return LogMessage::Tag::MODEL_RESULT;
    } else if constexpr(std::is_same<T, ModelDesign::Message>::value) {
      return LogMessage::Tag::MODEL_DESIGN;
    } else if constexpr(std::is_same<T, Message>::value) {
      return LogMessage::Tag::NONE;
    } else {
      static_assert(dependent_false<T>::value, "Enum declaration required");
    }
  }

  std::map<LogStreamId, std::reference_wrapper<std::ostream>> m_logStreams;
  std::map<LogStreamId, LogMessageFilter> m_filters;
  std::vector<LogStreamHunter> m_userHunters;
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

template<typename T, typename... Args>
void log(T msgType, Args... args) {
  LogProvider::instance().sendMessage(msgType, args...);
}

} // namespace Logger
} // namespace PowerLab

#endif // LOGGER_H
