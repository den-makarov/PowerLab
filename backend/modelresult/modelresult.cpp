#include <QFileDialog>
#include <QFile>

#include "backend/logger/logger.h"
#include "modelresult.h"
#include "modelresultvalidator.h"
#include "modelresultmeta.h"

// Dummy static fields to init as default values
ModelResult::DataPoints ModelResult::dummyPoints = {};

// Dummy static fields to init as default values
ModelResult::DataNames ModelResult::dummyNames = std::make_pair<std::string, std::string>("EMPTY", "UNIT");

ModelResult::ModelResult(QObject *parent)
  : QObject(parent)
  , m_validator(new ModelResultValidator())
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
//  E_DEBUG(this) << "New storage for"
//                << variables << "variables,"
//                << points << "points";

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
//    E_CRITICAL(this) << "Invalid variable identifier";
    return;
  }

//  E_DEBUG(this) << "New data point for variable id" << var
//                << ", point" << point;
  m_data[var].push_back(point);
}

/**
 * @brief ModelResult::addDataPoint
 * @param var
 * @param data
 */
void ModelResult::addDataPoint(size_t var, const DataPoints& data) {
  if(var >= m_data.size()) {
//    E_CRITICAL(this) << "Invalid variable identifier";
    return;
  }

//  E_DEBUG(this) << "New data point for variable id" << var
//                << ", points number" << data.size();

  m_data[var].insert(m_data[var].end(), data.begin(), data.end());
}

/**
 * @brief ModelResult::setDataNames
 * @param var
 * @param names
 */
const std::vector<ModelResultMeta::SignalDescriptor>* ModelResult::getSignalNames() const {
  return m_meta ? &m_meta->getData().signalSet : nullptr;
}

/**
 * @brief ModelResult::getDataPoints
 * @param var
 * @return
 */
const ModelResult::DataPoints& ModelResult::getDataPoints(size_t var) const {
  if(var >= m_signals.size()) {
    // @TODO: Consider to throw an exception

//    E_CRITICAL(this) << "Invalid variable identifier";
    return ModelResult::dummyPoints;
  }

  return m_data[var];
}

/**
 * @brief ModelResult::openFile
 */
void ModelResult::openFile() {
  QString filename = QFileDialog::getOpenFileName(nullptr,
                                                  tr("Open file with modeling results"),
                                                  "",
                                                  tr("Modeling result files (*.esk *.dat)"));
  if(filename.isEmpty()) {
//    E_DEBUG(this) << "No file selected";
    emit metaDataLoaded(nullptr, "No file selected");
    return;
  }

  if(m_validator->validate(filename.toStdString())) {
//    E_DEBUG(this) << "Meta data ready";
    m_meta = m_validator->getMetaData();
    if(m_meta) {
      init(m_meta->getData().varCount, m_meta->getData().points);
      emit metaDataLoaded(&m_meta->getData(), "Chose signals to plot");
    } else {
//      E_CRITICAL(this) << "Unable to retrive meta data";
      emit metaDataLoaded(nullptr, "Meta data is expected");
    }
  } else {
    emit metaDataLoaded(nullptr, "Meta data validation failed");
  }
}
