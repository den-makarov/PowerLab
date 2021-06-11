#include <iterator>

#include "logger.h"
#include "modelresult.h"
#include "modelresultvalidator.h"
#include "modelresultmeta.h"
#include "modelresultvalues.h"

namespace Model {

ModelResult::ModelResult()
  : m_validator(new ModelResultValidator())
{
  // EMPTY
}

ModelResult::~ModelResult() {
  if(m_validator) {
    delete m_validator;
    m_validator = nullptr;
  }
}

size_t ModelResult::getVariablesNumber() const {
  return m_meta ? m_meta->getData().varCount : 0;
}

size_t ModelResult::getPointsNumber() const {
  return m_meta ? m_meta->getData().points : 0;
}

void ModelResult::addSignalDataPoint(const SignalName& signalName, DataPoint point) {
  auto signalIt = m_signals.find(signalName);
  if(signalIt == m_signals.end()) {
    Logger::log(Model::ModelMessage::ERROR_UNKNOWN_SIGNAL_NAME, signalName);
    return;
  }

  Logger::log(Model::ModelMessage::DEBUG_NEW_DATA_POINT_FOR_SIGNAL, signalName, point);
  auto& signal = signalIt->second;
  signal.points.push_back(point);
}


void ModelResult::addSignalDataPoints(const SignalName& signalName,
                                      const SignalDataPoints& data) {
  auto signalIt = m_signals.find(signalName);
  if(signalIt == m_signals.end()) {
    Logger::log(Model::ModelMessage::ERROR_UNKNOWN_SIGNAL_NAME, signalName);
    return;
  }

  Logger::log(Model::ModelMessage::DEBUG_NEW_DATA_FOR_SIGNAL, signalName, data.size());
  auto& signal = signalIt->second;
  signal.points.insert(signal.points.end(), data.begin(), data.end());
}

template<typename DataIterator>
void ModelResult::addSignalDataPoints(const SignalName& signalName, DataIterator begin, DataIterator end) {
  auto signalIt = m_signals.find(signalName);
  if(signalIt == m_signals.end()) {
    Logger::log(Model::ModelMessage::ERROR_UNKNOWN_SIGNAL_NAME, signalName);
    return;
  }

  Logger::log(Model::ModelMessage::DEBUG_NEW_DATA_FOR_SIGNAL, signalName, std::distance(begin, end));
  auto& signal = signalIt->second;
  signal.points.insert(signal.points.end(), begin, end);
}


std::vector<ModelResult::SignalName> ModelResult::getAllSignalNames() const {
  std::vector<SignalName> result;
  for(auto& [key, value] : m_signals) {
    result.push_back(key);
  }

  return result;
}

ModelResult::SignalDataPoints ModelResult::getSignalDataPoints(const SignalName& name) const {
  auto signalIt = m_signals.find(name);
  if(signalIt == m_signals.end()) {
    Logger::log(Model::ModelMessage::ERROR_UNKNOWN_SIGNAL_NAME, name);
    return {};
  }

  auto& signal = signalIt->second;
  return signal.points;
}

void ModelResult::extractSignalsDataPoints(const std::string& filename) {
  auto signalCount = getVariablesNumber();
  auto* values = new ModelResultValue<double>(filename, getPointsNumber(), signalCount);

  const auto& signalDescriptors = m_meta->getData().signalSet;
  for(size_t i = 0; i < signalCount; i++) {
    SignalName signalName = signalDescriptors.at(i).name;
    m_signals[signalName] = {SignalDataPoints(), signalDescriptors.at(i)};
    addSignalDataPoints(signalName, values->getSignalPoints(i));
  }

  delete values;
}

void ModelResult::openFile(const std::string& filename) {
  if(filename.empty()) {
    Logger::log(Model::ModelMessage::DEBUG_NO_FILE_SELECTED);
    m_metaDataLoadCB(nullptr, "No file selected");
    return;
  }

  if(m_validator->validate(filename)) {
    Logger::log(Model::ModelMessage::DEBUG_META_DATA_READY);
    m_meta = m_validator->getMetaData();
    if(m_meta) {
      Logger::log(Model::ModelMessage::DEBUG_NEW_MODEL_RESULT_DATA,
                  getVariablesNumber(),
                  getPointsNumber());

      extractSignalsDataPoints(filename);
      m_metaDataLoadCB(&m_meta->getData(), "Chose signals to plot");
    } else {
      Logger::log(Model::ModelMessage::ERROR_META_DATA_NOT_READY);
      m_metaDataLoadCB(nullptr, "Meta data is expected");
    }
  } else {
    m_metaDataLoadCB(nullptr, "Meta data validation failed");
  }
}

void ModelResult::setupMetaDataLoadCB(ModelResult::MetaDataLoadCB cb) {
  if(cb) {
    m_metaDataLoadCB = cb;
  }
}

void ModelResult::defaultMetaDataLoadSignal(const ModelResultMeta::Data* data, const std::string& msg) {
  if(data) {
    Logger::log(Model::ModelMessage::DEBUG_DEFAULT_META_DATA_CALLBACK, &data, msg);
  } else {
    Logger::log(Model::ModelMessage::DEBUG_DEFAULT_META_DATA_CALLBACK, "No meta-data", msg);
  }
}

} // namespace Model
