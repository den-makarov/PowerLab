#ifndef MODELRESULTMETA_H
#define MODELRESULTMETA_H

#include <QObject>
#include <QDateTime>

#include "logger.h"

class ModelResultMeta : public QObject
{
  Q_OBJECT
public:
  using Signals = std::pair<QString, QString>;

  enum class TokenType {
    TITLE,
    DATE,
    PLOTNAME,
    FLAGS,
    VAR_COUNT,
    POINT_COUNT,
    SIGNALS,
    UNKNOWN
  };

  enum class Flags
  {
    REAL,
    UNKNOWN
  };

  struct Data {
    QString title = "";
    QString plotname = "";
    std::vector<Signals> signalSet;
    QDateTime date;
    size_t varCount = 0;
    size_t points = 0;
    Flags flags = Flags::UNKNOWN;
  };

  explicit ModelResultMeta(QObject *parent = nullptr);
  TokenType determineToken(const QString& str) const;
  bool addToken(TokenType type, const QString& str);
  void parseData();
  const Data& getData() const {
    return m_data;
  }

private:
  static const std::unordered_map<QString, TokenType> STR_TO_TOKEN_TYPE;

  struct Token {
    QString data;
    TokenType type;

    Signals splitToken(char delim) const {
      if(type == TokenType::SIGNALS) {
        auto list = data.trimmed().split(delim);
        E_DEBUG(nullptr) << data;
        E_DEBUG(nullptr) << list;
        return {list.first(), list.back()};
      } else {
        E_WARNING(nullptr) << "Token type doesn't support splitting data";
        return {"EMPTY", "UNIT"};
      }
    }
  };

  Data m_data;
  std::vector<Token> m_tokens;
};

QDebug operator<<(QDebug& log, const ModelResultMeta::Flags& data);
QDebug operator<<(QDebug& log, const ModelResultMeta::Data& data);

#endif // MODELRESULTMETA_H
