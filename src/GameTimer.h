#pragma once

#include <cstdint>

namespace ge {
class GameTimer {
public:
  GameTimer();
  double getFrameRate();
  double update();
  void startCap();
  void capFrameRate();

private:
  const double freq;
  const double stepsPerFrame;

  double previousTime;
  double startTime;
  double delta;
  uint64_t frames;
  uint32_t capTime;
};
}
