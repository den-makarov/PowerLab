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
  } else if(type == TokenType::SIGNALS) {
    auto list = str.splitRef('\t');
    result = addSignalToken(list);
  } else {
    auto pos = str.indexOf(':');
    if(pos != -1) {
      m_tokens.push_back({str.right(str.size() - pos - 1), type});
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
bool ModelResultMeta::addSignalToken(QVector<QStringRef>& list) {
  bool result = false;

  // @NOTE: If there are any signals, size of container should be definitely more than 2
  if(list.size() >= 2) {
    auto str_ref = list[0].trimmed().toString();
    str_ref.resize(str_ref.size() - 1);

    auto type = STR_TO_TOKEN_TYPE.find(str_ref);

    if(type == STR_TO_TOKEN_TYPE.end() || type->second != TokenType::SIGNALS) {
      E_CRITICAL(this) << "Can't parse signals. Wrong token type";
    } else {
      // @NOTE: each signal consists of number, signal name and signal units
      // for example: 0 Idd Amps
      // that is why each cycle a check should be performed to validate enough fields
      for(auto i = 1; i < list.size();) {
        Signals signal;

        if(i++ >= list.size() - 2) {
          E_CRITICAL(this) << "Corrupted signals string" << list[i];
          break;
        }

        signal.first = list[i].trimmed().toString();

        if(i++ >= list.size() - 1) {
          E_CRITICAL(this) << "Corrupted signals string" << list[i - 1];
          break;
        }

        signal.second = list[i].trimmed().toString();
        i++;

        m_data.signalSet.push_back(signal);

        if(i == list.size()) {
          // It is expected that last list item should be the second signal string (Unit)
          result = true;
        }
      }
    }
  } else {
    E_CRITICAL(this) << "Can't parse signals. No items to parse";
  }

  return result;
}

/**
 * @brief ModelResultMeta::parseToken
 * @param token
 * @param data
 */
void ModelResultMeta::parseToken(TokenType token, const QString& data) {
  switch(token) {
  case TokenType::TITLE:
    m_data.title = data.trimmed();
    break;
  case TokenType::DATE:
    m_data.date = QDateTime::fromString(data.trimmed(), Qt::RFC2822Date);
    break;
  case TokenType::PLOTNAME:
    m_data.plotname = data.trimmed();
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
    E_WARNING(this) << "Signals token type is parsed manualy";
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
