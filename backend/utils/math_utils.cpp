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
  segments.from = -1.0;
  segments.to = 1.0;
  segments.step = 0.5;

  return segments;
}

} // namespace Utilities
} // namespace PowerLab
