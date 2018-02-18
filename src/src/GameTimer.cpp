#include "../include/GameTimer.h"

#include <SDL.h>

using namespace ge;

GameTimer::GameTimer():
  freq(SDL_GetPerformanceFrequency()), stepsPerFrame(1000.0 / 60.0) {
  previousTime = 0.0;
  startTime = 0.0;
  frames = 0;
}

void GameTimer::startCap() {
  capTime = SDL_GetTicks();
}

void GameTimer::capFrameRate() {
  uint32_t loopTime = SDL_GetTicks() - capTime;
  if (loopTime < stepsPerFrame) {
    SDL_Delay(stepsPerFrame - loopTime);
  }
}

double GameTimer::getFrameRate() {
  return frames / ((previousTime - startTime) / freq);
}

double GameTimer::update() {
  double time = SDL_GetPerformanceCounter();

  if (previousTime == 0.0) {
    previousTime = time;
  }

  if (startTime == 0.0) {
    startTime = time;
  }

  delta = (time - previousTime) / freq;
  previousTime = time;

  frames++;

  return delta;
}
