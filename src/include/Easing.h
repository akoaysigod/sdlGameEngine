#pragma once

namespace ge {
  class Easing {
  public:
    Easing(double c1x, double c1y, double c2x, double c2y);
    double pointAtTime(double time);

    static Easing linear();
    static Easing easeIn();
    static Easing easeOut();
    static Easing easeInOut();

  private:
    const double c1x;
    const double c1y;
    const double c2x;
    const double c2y;

    const double s1x = 0.0;
    const double s1y = 0.0;
    const double s2x = 1.0;
    const double s2y = 1.0;
  };
}
