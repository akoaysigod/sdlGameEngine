#pragma once

namespace ge {
  class Point {
  public:
    Point(int x, int y);
    double distance(Point from);
    double duration(Point to);

  private:
    const int x;
    const int y;
  };
}
