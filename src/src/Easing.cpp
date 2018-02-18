#include "../include/Easing.h"

using namespace ge;

Easing::Easing(double c1x, double c1y, double c2x, double c2y):
  c1x(c1x), c1y(c1y), c2x(c2x), c2y(c2y) {}

double Easing::pointAtTime(double time) {
  // time needs to be >= 0.0 && <= 1.0
  auto oneminust = 1.0 - time;

  auto one = oneminust * oneminust * oneminust;
  auto two = 3 * time * oneminust * oneminust;
  auto thr = 3 * time * time * oneminust;
  auto fur = time * time * time;

  //return one * s1y + two * c1y + thr * c2y + fur * s2y;
  return one * s1x + two * c1x + thr * c2x + fur * s2x;
}

Easing Easing::linear() {
  return Easing(0.0, 0.0, 1.0, 1.0);
}

Easing Easing::easeIn() {
  return Easing(0.42, 0.0, 1.0, 1.0);
}

Easing Easing::easeOut() {
  return Easing(0.0, 0.0, 0.58, 1.0);
}

Easing Easing::easeInOut() {
  return Easing(0.42, 0.0, 0.58, 1.0);
}
