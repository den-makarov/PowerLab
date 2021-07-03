#ifndef MATH_UTILS_H
#define MATH_UTILS_H

namespace PowerLab {
namespace Utilities {

struct RoundedSegments {
  double from;
  double to;
  double step;
};

RoundedSegments findOptimalRoundedSegments(double from, double to, int minLimit, int maxLimit);

} // namespace Utilities
} // namespace PowerLab

#endif // STRING_UTILS_H
