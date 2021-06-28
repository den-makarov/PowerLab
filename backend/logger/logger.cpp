#include "logger.h"

namespace PowerLab {
namespace Logger {

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

LogProvider::PlacersFmt LogProvider::searchForPlacers(const std::string& format) const {
  LogProvider::PlacersFmt placers;
  int minPlacer = std::numeric_limits<int>::max();
  for(int j = static_cast<int>(format.size()) - 3; j >= 0; j--) {
    size_t i = static_cast<size_t>(j);
    if(format[i] == '%' && std::isdigit(format[i + 1])) {
      size_t cnt = 0;
      int placer = std::stoi(format.substr(i + 1), &cnt);
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

} // namespace Logger
} // namespace PowerLab
