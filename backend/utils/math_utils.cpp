#include <cmath>
#include <limits>

#include "math_utils.h"

namespace PowerLab {
namespace Utilities {

RoundedSegments findOptimalRoundedSegments(double from, double to, int minLimit, int maxLimit) {
  if(from >= to || minLimit <= 0 || maxLimit <= 0) {
    auto nan = std::numeric_limits<double>::quiet_NaN();
    return {nan, nan, nan};
  }

  RoundedSegments segments = {0, 0, 0};
  segments.from = -10;
  segments.to = 10;
  segments.step = 0.2;

  return segments;
}

} // namespace Utilities
} // namespace PowerLab
