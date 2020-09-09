#include "modelresultmeta.h"
#include "logger.h"

const std::unordered_map<QString, ModelResultMeta::TokenType> ModelResultMeta::STR_TO_TOKEN_TYPE = {
  {"Title", TokenType::TITLE},
  {"Date", TokenType::DATE},
  {"PlotName", TokenType::PLOTNAME},
  {"Flags", TokenType::FLAGS},
  {"No. Variables", TokenType::VAR_COUNT},
  {"No. Points", TokenType::POINT_COUNT},
  {"Variables", TokenType::SIGNALS}
};

ModelResultMeta::ModelResultMeta(QObject *parent) : QObject(parent)
{
  // EMPTY
}

void ModelResultMeta::addToken(const QString& str) {
  auto list = str.split(':');
  auto type = STR_TO_TOKEN_TYPE.find(list.first());
  if(type != STR_TO_TOKEN_TYPE.end()) {
    // @TODO parse variables in a different way
    m_tokens.push_back({list.back(), type->second});
  } else {
    m_tokens.push_back({str, TokenType::UNKNOWN});
  }
}

void ModelResultMeta::parseData() {
  for(const auto& item : m_tokens) {
    switch(item.type) {
    case TokenType::TITLE: m_data.title = item.data; break;
    case TokenType::DATE: m_data.date = QDate::fromString(item.data, Qt::RFC2822Date); break;
    case TokenType::PLOTNAME: m_data.plotname = item.data; break;
    case TokenType::FLAGS: m_data.flags = Flags::REAL; break;
    case TokenType::VAR_COUNT: m_data.varCount = item.data.toInt(); break;
    case TokenType::POINT_COUNT: m_data.points = item.data.toInt(); break;
    case TokenType::SIGNALS: m_data.signalSet.push_back(item.splitToken(' ')); break;
    case TokenType::UNKNOWN: E_WARNING(this) << "Unknown meta data type" << item.data;
      break;
    }
  }
}
