#include <QFileDialog>
#include <QFile>

#include "logger.h"
#include "modelresult.h"
#include "modelresultvalidator.h"
#include "modelresultmeta.h"

// Dummy static fields to init as default values
ModelResult::DataPoints ModelResult::dummyPoints = {};

// Dummy static fields to init as default values
ModelResult::DataNames ModelResult::dummyNames = std::make_pair<std::string, std::string>("EMPTY", "UNIT");

ModelResult::ModelResult(QObject *parent)
  : QObject(parent)
  , m_validator(new ModelResultValidator(parent))
{
  // EMPTY
}

/**
 * @brief ModelResult::init. Initialize internal storage for new data
 *
 * @param variables: number of signals in model result
 * @param points: number of points of each signal
 */
void ModelResult::init(size_t variables, size_t points) {
  E_DEBUG(this) << "New storage for"
                << variables << "variables,"
                << points << "points";

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
  return m_data.size();
}

/**
 * @brief ModelResult::getPointsNumber
 * @return
 */
size_t ModelResult::getPointsNumber() const {
  if(m_data.empty()) {
    return 0;
  }

  return m_data[0].size();
}

/**
 * @brief ModelResult::addDataPoint
 * @param var
 * @param point
 */
void ModelResult::addDataPoint(size_t var, double point) {
  if(var >= m_data.size()) {
    E_CRITICAL(this) << "Invalid variable identifier";
    return;
  }

  E_DEBUG(this) << "New data point for variable id" << var
                << ", point" << point;
  m_data[var].push_back(point);
}

/**
 * @brief ModelResult::addDataPoint
 * @param var
 * @param data
 */
void ModelResult::addDataPoint(size_t var, const DataPoints& data) {
  if(var >= m_data.size()) {
    E_CRITICAL(this) << "Invalid variable identifier";
    return;
  }

  E_DEBUG(this) << "New data point for variable id" << var
                << ", points number" << data.size();

  m_data[var].insert(m_data[var].end(), data.begin(), data.end());
}

/**
 * @brief ModelResult::setDataNames
 * @param var
 * @param names
 */
void ModelResult::setDataNames(size_t var, DataNames& names) {
  if(var >= m_signals.size()) {
    E_CRITICAL(this) << "Invalid variable identifier";
    return;
  }

  E_DEBUG(this) << "Update variable id" << var
                << ", title:" << names.first.c_str()
                << ", units:" << names.second.c_str();

  m_signals[var] = names;
}

/**
 * @brief ModelResult::getDataPoints
 * @param var
 * @return
 */
const ModelResult::DataPoints& ModelResult::getDataPoints(size_t var) const {
  if(var >= m_signals.size()) {
    // @TODO: Consider to throw an exception

    E_CRITICAL(this) << "Invalid variable identifier";
    return ModelResult::dummyPoints;
  }

  return m_data[var];
}

/**
 * @brief ModelResult::getDataNames
 * @param var
 * @return
 */
const ModelResult::DataNames& ModelResult::getDataNames(size_t var) const {
  if(var >= m_signals.size()) {
    // @TODO: Consider to throw an exception

    E_CRITICAL(this) << "Invalid variable identifier";
    return ModelResult::dummyNames;
  }

  return m_signals[var];
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
    E_DEBUG(this) << "No file selected";
    return;
  }

  if(m_validator->validate(filename)) {
    E_DEBUG(this) << "Meta data ready";
    auto meta = m_validator->getMetaData();
    if(meta) {
      init(meta->getData().varCount, meta->getData().points);
    } else {
      E_CRITICAL(this) << "Unable to retrive meta data";
    }
  }
}
