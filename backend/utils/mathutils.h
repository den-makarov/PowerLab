#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <iostream>

namespace PowerLab {
namespace Utilities {

static constexpr double PI = 3.14159265;

struct RoundedSegments {
  double from;
  double to;
  double step;
};

int orderOfTen(double value);

double radianToDegree(double rad);
double degreeToRadian(double degree);

RoundedSegments findOptimalRoundedSegments(double from, double to, int maxStepNumber);
std::ostream& operator<<(std::ostream& out, const RoundedSegments& rs);

} // namespace Utilities
} // namespace PowerLab

#endif // STRING_UTILS_H
