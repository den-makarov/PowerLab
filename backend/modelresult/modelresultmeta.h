#ifndef MODELRESULTMETA_H
#define MODELRESULTMETA_H

#include <ctime>
#include <string_view>
#include <iostream>

#include "logger.h"

namespace PowerLab {
namespace Model {

class ModelResultMeta {
public:
  enum class TokenType {
    TITLE,
    DATE,
    PLOTNAME,
    FLAGS,
    VAR_COUNT,
    POINT_COUNT,
    SIGNALS,
    VALUES,
    UNKNOWN
  };

  enum class Flags {
    REAL,
    UNKNOWN
  };

  enum class UnitType {
    TIME,
    VOLTAGE,
    CURRENT,
    UNITLESS
  };

  static std::string convertUnitTypeToString(UnitType type);
  static std::string convertUnitTypeToISSymbol(UnitType type);
  static UnitType convertUnitTypeFromString(const std::string& str);

  struct SignalDescriptor {
    UnitType unit = UnitType::UNITLESS;
    std::string name;
  };

  struct Data {
    size_t varCount = 0;
    size_t points = 0;
    std::string title = "";
    std::string plotname = "";
    time_t timeStamp;
    Flags flags = Flags::UNKNOWN;
    std::vector<SignalDescriptor> signalSet;
  };

  ModelResultMeta() = default;

  TokenType determineToken(const std::string& str) const;
  bool addToken(TokenType type, const std::string& str);
  std::string_view peekTokenData(TokenType token) const;
  void parseData();
  const Data& getData() const {
    return m_data;
  }

private:
  static const std::unordered_map<std::string, TokenType> STR_TO_TOKEN_TYPE;

  struct Token {
    std::string data;
    TokenType type;

    SignalDescriptor splitToken(char delim) const;
  };

  Data m_data;
  std::vector<Token> m_tokens;

  void parseToken(TokenType token, const std::string& data);
  void parseSignalToken(const std::string& str);
};

std::ostream& operator<<(std::ostream& out, ModelResultMeta::TokenType token);
std::ostream& operator<<(std::ostream& out, const ModelResultMeta::Flags& data);
std::ostream& operator<<(std::ostream& out, const ModelResultMeta::SignalDescriptor& signal);
std::ostream& operator<<(std::ostream& out, const ModelResultMeta::Data& data);

} // namespace Model
} // namespace PowerLab

#endif // MODELRESULTMETA_H
