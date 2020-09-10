#include "modelresultmeta.h"
#include "logger.h"

const std::unordered_map<QString, ModelResultMeta::TokenType> ModelResultMeta::STR_TO_TOKEN_TYPE = {
  {"Title", TokenType::TITLE},
  {"Date", TokenType::DATE},
  {"Plotname", TokenType::PLOTNAME},
  {"Flags", TokenType::FLAGS},
  {"No. Variables", TokenType::VAR_COUNT},
  {"No. Points", TokenType::POINT_COUNT},
  {"Variables", TokenType::SIGNALS}
};

ModelResultMeta::ModelResultMeta(QObject *parent) : QObject(parent)
{
  // EMPTY
}

bool ModelResultMeta::addToken(const QString& str) {
  bool result = false;
  auto list = str.split(':');
  auto type = STR_TO_TOKEN_TYPE.find(list.first());
  if(type != STR_TO_TOKEN_TYPE.end()) {
    // @TODO parse variables in a different way
    // @TODO parse date in a different way
    if(type->second == TokenType::DATE) {
      auto pos = str.size() - type->first.size() - 1;
      m_tokens.push_back({str.right(pos), type->second});
    } else {
      m_tokens.push_back({list.back(), type->second});
    }

    result = true;
  } else {
    m_tokens.push_back({str, TokenType::UNKNOWN});
    result = false;
  }
  return result;
}

void ModelResultMeta::parseData() {
  for(const auto& item : m_tokens) {
    switch(item.type) {
    case TokenType::TITLE:
      m_data.title = item.data.trimmed();
      break;
    case TokenType::DATE:
      m_data.date = QDateTime::fromString(item.data.trimmed(), Qt::RFC2822Date);
      break;
    case TokenType::PLOTNAME:
      m_data.plotname = item.data.trimmed();
      break;
    case TokenType::FLAGS:
      m_data.flags = Flags::REAL;
      break;
    case TokenType::VAR_COUNT:
      m_data.varCount = item.data.toUInt();
      break;
    case TokenType::POINT_COUNT:
      m_data.points = item.data.toUInt();
      break;
    case TokenType::SIGNALS:
      m_data.signalSet.push_back(item.splitToken(' '));
      break;
    case TokenType::UNKNOWN:
      E_WARNING(this) << "Unknown meta data type" << item.data;
      break;
    }
  }
}

QDebug operator<<(QDebug& log, const ModelResultMeta::Flags& data) {
  switch(data) {
  case ModelResultMeta::Flags::REAL: log << "REAL"; break;
  case ModelResultMeta::Flags::UNKNOWN: log << "UNKNOWN"; break;
  }
  return log;
}

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
