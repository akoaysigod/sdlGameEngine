#include "../include/Point.h"

#include <cmath>

using namespace ge;

Point::Point(int x, int y): x(x), y(y) {}

double Point::distance(Point from) {
  return std::sqrt(std::pow(x - from.x, 2) + std::pow(y - from.y, 2));
}

double Point::duration(Point to) {
  auto distance = this->distance(to);
  return 0.015 * distance;
}
/*
  func distanceFrom(from: RLGCoordinate) -> Float {
    let dx = fabsf(Float(self.x - from.x))
    let dy = fabsf(Float(self.y - from.y))
    return sqrt((dx * dx) + (dy * dy))
  }

  func duration(toPoint: RLGCoordinate) -> NSTimeInterval {
    let dist = sqrt(pow(toPoint.position.x - self.position.x, 2) + pow(toPoint.position.y - self.position.y, 2))
    return NSTimeInterval(0.015 * dist)
  }
*/
