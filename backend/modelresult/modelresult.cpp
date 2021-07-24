#include <iterator>

#include "logger.h"
#include "modelresult.h"
#include "modelresultvalidator.h"
#include "modelresultmeta.h"
#include "modelresultvalues.h"

namespace PowerLab {
namespace ModelResult {

ModelResult::ModelResult()
  : m_validator(new ModelResultValidator())
{
  // EMPTY
}

std::string ModelResult::getModelTitle() const {
  return m_validator->getMetaData().getData().plotname;
}

size_t ModelResult::getVariablesNumber() const {
  return m_validator ? m_validator->getMetaData().getData().varCount : 0;
}

size_t ModelResult::getPointsNumber() const {
  return m_validator ? m_validator->getMetaData().getData().points : 0;
}

void ModelResult::addSignalDataPoint(const SignalName& signalName, DataPoint point) {
  auto signalIt = m_signals.find(signalName);
  if(signalIt == m_signals.end()) {
    Logger::log(Message::ERROR_UNKNOWN_SIGNAL_NAME, signalName);
    return;
  }

  Logger::log(Message::DEBUG_NEW_DATA_POINT_FOR_SIGNAL, signalName, point);
  auto& signal = signalIt->second;
  signal.points.push_back(point);
}

void ModelResult::addSignalDataPoints(const SignalName& signalName,
                                      const SignalDataPoints& data) {
  auto signalIt = m_signals.find(signalName);
  if(signalIt == m_signals.end()) {
    Logger::log(Message::ERROR_UNKNOWN_SIGNAL_NAME, signalName);
    return;
  }

  Logger::log(Message::DEBUG_NEW_DATA_FOR_SIGNAL, signalName, data.size());
  auto& signal = signalIt->second;
  signal.points.insert(signal.points.end(), data.begin(), data.end());
}

template<typename DataIterator>
void ModelResult::addSignalDataPoints(const SignalName& signalName, DataIterator begin, DataIterator end) {
  auto signalIt = m_signals.find(signalName);
  if(signalIt == m_signals.end()) {
    Logger::log(Message::ERROR_UNKNOWN_SIGNAL_NAME, signalName);
    return;
  }

  Logger::log(Message::DEBUG_NEW_DATA_FOR_SIGNAL, signalName, std::distance(begin, end));
  auto& signal = signalIt->second;
  signal.points.insert(signal.points.end(), begin, end);
}

ModelResult::SignalName ModelResult::getReferenceSignalName() const {
  for(auto& [key, value] : m_signals) {
    if(value.isReference) {
      return key;
    }
  }

  return SignalName();
}

std::vector<ModelResult::SignalName> ModelResult::getAllSignalNames() const {
  std::vector<SignalName> result;
  for(auto& [key, value] : m_signals) {
    if(!value.isReference) {
      result.push_back(key);
    }
  }

  return result;
}

std::string ModelResult::getSignalUnitsSISymbol(const std::string& signalName) const {
  return ModelResultMeta::convertUnitTypeToISSymbol(m_signals.at(signalName).signal.unit);
}

ModelResult::SignalDataPoints ModelResult::getSignalDataPoints(const SignalName& name) const {
  auto signalIt = m_signals.find(name);
  if(signalIt == m_signals.end()) {
    Logger::log(Message::ERROR_UNKNOWN_SIGNAL_NAME, name);
    return {};
  }

  auto& signal = signalIt->second;
  return signal.points;
}

void ModelResult::extractSignalsDataPoints(const std::string& filename) {
  auto signalCount = getVariablesNumber();


  if(m_validator) {
    auto values = std::make_unique<ModelResultValue<double>>(filename, getPointsNumber(), signalCount);
    const auto& signalDescriptors = m_validator->getMetaData().getData().signalSet;
    for(size_t i = 0; i < signalCount; i++) {
      bool signalDataUsedAsHorizontalPoints = i == 0 ? true : false;
      SignalName signalName = signalDescriptors.at(i).name;
      m_signals[signalName] = {SignalDataPoints(),
                               signalDescriptors.at(i),
                               signalDataUsedAsHorizontalPoints};
      addSignalDataPoints(signalName, values->getSignalPoints(i));
    }
  } else {
    Logger::log(Message::ERROR_META_DATA_NOT_READY);
  }
}

void ModelResult::openFile(const std::string& filename) {
  if(filename.empty()) {
    Logger::log(Message::DEBUG_NO_FILE_SELECTED);
    m_metaDataLoadCB(false, "No file selected");
    return;
  }

  if(m_validator->validate(filename)) {
    Logger::log(Message::DEBUG_NEW_MODEL_RESULT_DATA,
                  getVariablesNumber(),
                  getPointsNumber());

    extractSignalsDataPoints(filename);
    Logger::log(Message::DEBUG_META_DATA_READY);
    m_metaDataLoadCB(true, "Chose signals to plot");
  } else {
    m_metaDataLoadCB(false, "Meta data validation failed");
  }
}

void ModelResult::setupMetaDataLoadCB(ModelResult::MetaDataLoadCB cb) {
  if(cb) {
    m_metaDataLoadCB = cb;
  }
}

void ModelResult::defaultMetaDataLoadSignal(bool parseResult, const std::string& msg) {
  if(parseResult) {
    Logger::log(Message::DEBUG_DEFAULT_META_DATA_CALLBACK, "Parsing success", msg);
  } else {
    Logger::log(Message::DEBUG_DEFAULT_META_DATA_CALLBACK, "Parsing failed", msg);
  }
}

} // namespace ModelResult
} // namespace PowerLab
