#include "backend/logger/logger.h"
#include "modelresult.h"
#include "modelresultvalidator.h"
#include "modelresultmeta.h"

// Dummy static fields to init as default values
ModelResult::DataPoints ModelResult::dummyPoints = {};

// Dummy static fields to init as default values
ModelResult::DataNames ModelResult::dummyNames = std::make_pair<std::string, std::string>("EMPTY", "UNIT");

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

/**
 * @brief ModelResult::init. Initialize internal storage for new data
 *
 * @param variables: number of signals in model result
 * @param points: number of points of each signal
 */
void ModelResult::init(size_t variables, size_t points) {
  Logger::log(Model::ModelMessage::DEBUG_NEW_MODEL_RESULT_STORAGE, variables, points);

  if(variables > MAX_VARIABLES_NUMBER || points > MAX_POINTS_NUMBER) {
    variables = 0;
    points = 0;
  }

  m_data = std::vector<DataPoints>(variables);
  for(auto& item : m_data) {
    item.reserve(points);
  }

  m_signals = std::vector<DataNames>(variables);
  for(auto& item : m_signals) {
    item = ModelResult::dummyNames;
  }
}

/**
 * @brief ModelResult::getVariablesNumber
 * @return
 */
size_t ModelResult::getVariablesNumber() const {
  return m_meta ? m_meta->getData().varCount : 0;
}

/**
 * @brief ModelResult::getPointsNumber
 * @return
 */
size_t ModelResult::getPointsNumber() const {
  return m_meta ? m_meta->getData().points : 0;
}

/**
 * @brief ModelResult::addDataPoint
 * @param var
 * @param point
 */
void ModelResult::addDataPoint(size_t var, double point) {
  if(var >= m_data.size()) {
    Logger::log(Model::ModelMessage::ERROR_INVALID_SIGNAL_ID, var);
    return;
  }

  Logger::log(Model::ModelMessage::DEBUG_NEW_DATA_POINT_FOR_SIGNAL, var, point);
  m_data[var].push_back(point);
}

/**
 * @brief ModelResult::addDataPoint
 * @param var
 * @param data
 */
void ModelResult::addDataPoint(size_t var, const DataPoints& data) {
  if(var >= m_data.size()) {
    Logger::log(Model::ModelMessage::ERROR_INVALID_SIGNAL_ID, var);
    return;
  }

  Logger::log(Model::ModelMessage::DEBUG_NEW_DATA_FOR_SIGNAL, var, data.size());
  m_data[var].insert(m_data[var].end(), data.begin(), data.end());
}

/**
 * @brief ModelResult::setDataNames
 * @param var
 * @param names
 */
const ModelResult::SignalNames* ModelResult::getSignalNames() const {
  return m_meta ? &m_meta->getData().signalSet : nullptr;
}

/**
 * @brief ModelResult::getDataPoints
 * @param var
 * @return
 */
const ModelResult::DataPoints& ModelResult::getDataPoints(size_t var) const {
  if(var >= m_signals.size()) {
    Logger::log(Model::ModelMessage::ERROR_INVALID_SIGNAL_ID, var);
    return ModelResult::dummyPoints;
  }

  return m_data[var];
}

/**
 * @brief ModelResult::openFile
 */
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
      init(m_meta->getData().varCount, m_meta->getData().points);
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
