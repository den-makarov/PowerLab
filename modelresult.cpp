#include <logger.h>
#include "modelresult.h"

static ModelResult::DataPoints dummyPoints = {};
static ModelResult::DataNames dummyNames = std::make_pair<std::string, std::string>("EMPTY", "UNIT");

ModelResult::ModelResult(size_t variables, size_t points, QObject *parent) : QObject(parent)
{
  E_DEBUG(this) << "New storage for #"
                << variables << "variables, #"
                << points << "points";

  m_data = std::vector<DataPoints>(variables);
  for(auto& item : m_data) {
    item.reserve(points);
  }

  m_signals = std::vector<DataNames>(variables);
  for(auto& item : m_signals) {
    item = dummyNames;
  }
}

size_t ModelResult::getVariablesNumber() const {
  return m_data.size();
}

size_t ModelResult::getPointsNumber() const {
  if(m_data.empty()) {
    return 0;
  }

  return m_data[0].size();
}

void ModelResult::addDataPoint(size_t var, double point) {
  if(var >= m_data.size()) {
    E_CRITICAL(this) << "Invalid variable identifier";
    return;
  }

  E_DEBUG(this) << "New data point for variable id " << var
                << ", point " << point;
  m_data[var].push_back(point);
}

void ModelResult::addDataPoint(size_t var, const DataPoints& data) {
  if(var >= m_data.size()) {
    E_CRITICAL(this) << "Invalid variable identifier";
    return;
  }

  E_DEBUG(this) << "New data point for variable id " << var
                << ", points number " << data.size();

  m_data[var].insert(m_data[var].end(), data.begin(), data.end());
}

void ModelResult::setDataNames(size_t var, DataNames& names) {
  if(var >= m_signals.size()) {
    E_CRITICAL(this) << "Invalid variable identifier";
    return;
  }

  E_DEBUG(this) << "Update variable id " << var
                << ", title: " << names.first.c_str()
                << ", units: " << names.second.c_str();

  m_signals[var] = names;
}

const ModelResult::DataPoints& ModelResult::getDataPoints(size_t var) const {
  if(var >= m_signals.size()) {
    // @TODO: Consider to throw an exception

    E_CRITICAL(this) << "Invalid variable identifier";
    return dummyPoints;
  }

  return m_data[var];
}

const ModelResult::DataNames& ModelResult::getDataNames(size_t var) const {
  if(var >= m_signals.size()) {
    // @TODO: Consider to throw an exception

    E_CRITICAL(this) << "Invalid variable identifier";
    return dummyNames;
  }

  return m_signals[var];
}
