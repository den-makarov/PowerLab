#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <vector>
#include <string>
#include <ctime>

namespace Utilities {

enum class DateFormat {
  RFC2822Date
};

std::time_t dateFromString(const std::string& str, DateFormat format);
std::string trimString(const std::string& str);
std::vector<std::string> splitString(const std::string& str, char delim);

} // namespace Utilities
#endif // STRING_UTILS_H
