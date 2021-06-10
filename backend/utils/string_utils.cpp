#include <sstream>
#include <iomanip>

#include "string_utils.h"

namespace Utilities {

std::time_t dateFromString(const std::string& str, DateFormat format) {
  std::time_t time = 0;
  switch(format) {
    case DateFormat::RFC2822Date: {
      std::istringstream date(str);
      std::tm tm{};
      date >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
      time = std::mktime(&tm);
    }
    break;
  }

  return time;
}

std::string trimString(const std::string& str) {
  std::string result;
  size_t pos = 0;
  while(pos < str.size()) {
    if(str[pos] == ' ' || str[pos] == '\t' || str[pos] == '\n') {
      pos++;
    } else {
      break;
    }
  }
  result = str.substr(pos);
  while(!result.empty()) {
    if(result.back() == ' ' || result.back() == '\t' || result.back() == '\n') {
      result.pop_back();
    } else {
      break;
    }
  }

  return result;
}

std::vector<std::string> splitString(const std::string& str, char delim) {
  std::vector<std::string> result;
  size_t begin = 0;
  size_t end = str.find(delim);
  while(end != std::string::npos) {
    result.push_back(str.substr(begin, end - begin));
    begin = end + 1;
    end = str.find(delim, begin);
  }

  if(begin != 0) {
    result.push_back(str.substr(begin, str.size() - begin));
  }

  return result;
}

} // namespace Utilities
