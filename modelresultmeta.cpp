#include "modelresultmeta.h"
#include "logger.h"

// Map for search token
const std::unordered_map<QString, ModelResultMeta::TokenType> ModelResultMeta::STR_TO_TOKEN_TYPE = {
  {"Title", TokenType::TITLE},
  {"Date", TokenType::DATE},
  {"Plotname", TokenType::PLOTNAME},
  {"Flags", TokenType::FLAGS},
  {"No. Variables", TokenType::VAR_COUNT},
  {"No. Points", TokenType::POINT_COUNT},
  {"Variables", TokenType::SIGNALS}
};

/**
 * @brief ModelResultMeta::ModelResultMeta
 * @param parent
 */
ModelResultMeta::ModelResultMeta(QObject *parent) : QObject(parent)
{
  // EMPTY
}

/**
 * @brief ModelResultMeta::~ModelResultMeta
 */
ModelResultMeta::~ModelResultMeta() {
  E_DEBUG(this) << "Destructor";
}

/**
 * @brief ModelResultMeta::determineToken
 * @param str
 * @return
 */
ModelResultMeta::TokenType ModelResultMeta::determineToken(const QString& str) const {
  TokenType token = TokenType::UNKNOWN;

  auto list = str.splitRef(':');
  if(!list.isEmpty()) {
    auto type = STR_TO_TOKEN_TYPE.find(list[0].toString());
    if(type != STR_TO_TOKEN_TYPE.end()) {
     token = type->second;
   }
  }

  return token;
}

/**
 * @brief ModelResultMeta::addToken
 * @param type
 * @param str
 * @return
 */
bool ModelResultMeta::addToken(ModelResultMeta::TokenType type, const QString& str) {
  bool result = false;

  if(type == TokenType::UNKNOWN) {
    E_CRITICAL(this) << "Attempt to add UNKNOWN token" << str;
  } else {
    auto pos = str.indexOf(':');
    if(pos != -1) {
      m_tokens.push_back({str.right(str.size() - pos - 1).trimmed(), type});
      result = true;
    }
  }

  return result;
}

/**
 * @brief ModelResultMeta::addSignalToken
 * @param list
 * @return
 */
void ModelResultMeta::parseSignalToken(const QString& str) {
  auto list = str.splitRef('\t');
  // @NOTE: If there are any signals, size of container should be definitely more than 2
  // and number of items should be ratio of 3
  if(list.size() > 2 && !(list.size() % 3)) {
    auto str_ref = list[0].trimmed().toString();
    str_ref.resize(str_ref.size() - 1);

    // @NOTE: each signal consists of number, signal name and signal units
    // for example: 0 Idd Amps
    for(auto i = 0; i < list.size();) {
      Signals signal;
      signal.first = list[++i].trimmed().toString();
      signal.second = list[++i].trimmed().toString();
      m_data.signalSet.push_back(signal);
      i++;
    }
  } else {
    E_CRITICAL(this) << "Can't parse signals. No items to parse";
  }
}

/**
 * @brief ModelResultMeta::peekTokenData
 * @param token
 * @return
 */
QStringRef ModelResultMeta::peekTokenData(TokenType token) const {
  for(const auto & item : m_tokens) {
    if(item.type == token) {
      return &item.data;
    }
  }

  return QStringRef();
}


/**
 * @brief ModelResultMeta::parseToken
 * @param token
 * @param data
 */
void ModelResultMeta::parseToken(TokenType token, const QString& data) {
  switch(token) {
  case TokenType::TITLE:
    m_data.title = data;
    break;
  case TokenType::DATE:
    m_data.date = QDateTime::fromString(data, Qt::RFC2822Date);
    break;
  case TokenType::PLOTNAME:
    m_data.plotname = data;
    break;
  case TokenType::FLAGS:
    m_data.flags = Flags::REAL;
    break;
  case TokenType::VAR_COUNT:
    m_data.varCount = data.toUInt();
    break;
  case TokenType::POINT_COUNT:
    m_data.points = data.toUInt();
    break;
  case TokenType::SIGNALS:
    parseSignalToken(data);
    break;
  case TokenType::UNKNOWN:
    E_WARNING(this) << "Unknown meta data type" << data;
    break;
  }
}

/**
 * @brief ModelResultMeta::parseData
 */
void ModelResultMeta::parseData() {
  for(const auto& item : m_tokens) {
    parseToken(item.type, item.data);
  }
}

/**
 * @brief operator <<
 * @param log
 * @param data
 * @return
 */
QDebug operator<<(QDebug& log, const ModelResultMeta::Flags& data) {
  switch(data) {
  case ModelResultMeta::Flags::REAL: log << "REAL"; break;
  case ModelResultMeta::Flags::UNKNOWN: log << "UNKNOWN"; break;
  }
  return log;
}

/**
 * @brief operator <<
 * @param log
 * @param data
 * @return
 */
QDebug operator<<(QDebug& log, const ModelResultMeta::Data& data) {
  log << "Model result meta data:\n";
  log << "Title:" << data.title << "\n";
  log << "Plotname:" << data.plotname << "\n";
  log << "Date:" << data.date.toString("yyyy/MM/dd hh:mm:ss") << "\n";
  log << "Flags:" << data.flags << "\n";
  log << "Number of signals" << data.varCount << data.signalSet << "\n";
  log << "Number of points" << data.points;
  return log;
}
