#ifndef MODELRESULTVALUE_H
#define MODELRESULTVALUE_H

#include <cassert>
#include <string>
#include <vector>
#include <fstream>

#include "stringutils.h"
#include "logger.h"

namespace PowerLab {
namespace ModelResult {

template <typename T = double>
class ModelResultValue {
  static constexpr size_t MAX_SIGNAL_COUNT = 10;
public:
  explicit ModelResultValue(const std::string& filename, size_t pointsCount, size_t signalsCount)
    : m_filename(filename)
    , m_values(signalsCount, std::vector<T>(pointsCount))
  {
    assert(signalsCount != 0);

    std::ifstream file(m_filename);

    if(!file.is_open()) {
      Logger::log(Message::ERROR_VALUES_FILE_NOT_OPEN, filename);
      return;
    }

    bool valuesFound = false;
    for(std::string line; std::getline(file, line); ) {
      auto list = Utilities::splitString(line, ':');
      if(!list.empty() && list[0] == "Values") {
        readValues(file);
        valuesFound = true;
        break;
      }
    }

    if(!valuesFound) {
      Logger::log(Message::ERROR_VALUES_NOT_FOUND, filename);
    }
  }

  std::vector<T> getSignalPoints(size_t signalIdx) const {
    return m_values.at(signalIdx);
  }

private:
  void readValues(std::istream& file) {
    while(!file.eof()) {
      size_t dataPointCounter = 0;
      file >> dataPointCounter;

      if(dataPointCounter >= m_values.at(0).size()) {
        Logger::log(Message::ERROR_DATA_POINT_INDEX_INVALID,
                    dataPointCounter,
                    m_values[0].size());
        break;
      }

      for(size_t signalCounter = 0; signalCounter < m_values.size(); signalCounter++) {
        auto& value = m_values.at(signalCounter).at(dataPointCounter);
        file >> value;
        if(file.eof()) {
          Logger::log(Message::ERROR_VALUES_UNEXPECTED_END,
                      m_values.size(),
                      m_values[0].size(),
                      dataPointCounter);
          break;
        }
      }

      if(dataPointCounter == m_values.at(0).size() - 1) {
        Logger::log(Message::DEBUG_VALUES_FILE_EXPECTED_END_REACHED);
        break;
      }
    }
  }


  const std::string m_filename;
  std::vector<std::vector<T>> m_values;
};

} // namespace ModelResult
} // namespace PowerLab

#endif // MODELRESULTVALUE_H
