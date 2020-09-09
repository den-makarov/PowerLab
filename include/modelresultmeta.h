#ifndef MODELRESULTMETA_H
#define MODELRESULTMETA_H

#include <QObject>
#include <QDate>
#include <QTime>

class ModelResultMeta : public QObject
{
  Q_OBJECT
public:
  using Signals = std::pair<QString, QString>;

  enum class Flags
  {
    REAL
  };

  struct Data {
    QString title;
    QString plotname;
    std::vector<Signals> signalSet;
    QDate date;
//    QTime time;
    int varCount;
    int points;
    Flags flags;
  };

  explicit ModelResultMeta(QObject *parent = nullptr);
  void addToken(const QString& str);
  void parseData();
  const Data& getData() const {
    return m_data;
  }

private:
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

  static const std::unordered_map<QString, TokenType> STR_TO_TOKEN_TYPE;

  struct Token {
    QString data;
    TokenType type;

    Signals splitToken(char delim) const {
      if(type == TokenType::SIGNALS) {
        auto list = data.split(delim);
        return {list.first(), list.back()};
      } else {
        return {"EMPTY", "UNIT"};
      }
    }
  };

  Data m_data;
  std::vector<Token> m_tokens;
};

#endif // MODELRESULTMETA_H
