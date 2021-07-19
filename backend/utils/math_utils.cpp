#include <cmath>
#include <limits>
#include <set>

#include "math_utils.h"

namespace PowerLab {
namespace Utilities {

RoundedSegments findOptimalRoundedSegments(double from, double to, int maxStepNumber) {
  if(from >= to || maxStepNumber <= 0) {
    auto nan = std::numeric_limits<double>::quiet_NaN();
    return {nan, nan, nan};
  }

  RoundedSegments segments = {from, to, (to - from) / maxStepNumber};
  auto minStep = (to - from) / maxStepNumber;

  double div = 1.0;
  while(minStep < 0.5 || 20.0 < minStep) {
    if(minStep > 10.0) {
      div *= 10.0;
      minStep /= 10.0;
    } else {
      div /= 10.0;
      minStep *= 10.0;
    }
  }

  if(minStep <= 1.0) {
    minStep = 1.0 * div;
  } else if(minStep <= 2.0) {
    minStep = 2.0 * div;
  } else if(minStep <= 2.5) {
    minStep = 2.5 * div;
  } else if(minStep <= 5.0) {
    minStep = 5.0 * div;
  } else {
    minStep = 10.0 * div;
  }

  int fromDiv = static_cast<int>(from / minStep);
  segments.from = fromDiv * minStep;
  int toDiv = static_cast<int>(to / minStep);
  segments.to = toDiv * minStep;
  segments.step = minStep;

  return segments;
}

int orderOfTen(double value) {
  int result = 0;

  if(std::fabs(value) < 10 * std::numeric_limits<double>::epsilon()) {
    return result;
  }

  if(std::fabs(value) > 10.0) {
    while(std::fabs(value) > 10.0) {
      value /= 10;
      result++;
    }
  } else {
    while(std::fabs(value) < 1.0) {
      value *= 10;
      result--;
    }
  }

  return result;
}

std::ostream& operator<<(std::ostream& out, const RoundedSegments& rs) {
  out << "Segments: {" << rs.from
      << ", " << rs.to
      << ", " << rs.step << "}";

  if(!(std::isnan(rs.from) || std::isnan(rs.to) || std::isnan(rs.step))) {
    int cnt = static_cast<int>((rs.to - rs.from) / rs.step);
    out << " [";
    for(auto i = rs.from; i < rs.to && cnt >= 0; i += rs.step, cnt--) {
      out << i << ", ";
    }
    out << rs.to << "]";
  }

  return out;
}

} // namespace Utilities
} // namespace PowerLab
