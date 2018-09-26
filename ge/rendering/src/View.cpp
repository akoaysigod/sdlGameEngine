#include <SDL.h>

#include "../include/ge/View.h"
#include "../../utils/include/ge/GameTimer.h"
#include "../../init/include/ge/Init.h"
#include "../include/ge/Renderer.h"
#include "../../nodes/include/ge/Scene.h"

#include <iostream>

using namespace ge;

View::View(const Window &window,
           const int &red,
           const int &green,
           const int &blue):
  gameTimer(std::make_unique<GameTimer>()),
  renderer(std::make_shared<Renderer>(window, red, green, blue))
{
  // this does not work in here, find out why
  // or move these out which kind of sucks

  //if (!Init::SDL()) {
  //  Init::quitSDL();
  //  throw "Unable to initialize SDL.";
  //}

  //if (!Init::SDLTTF()) {
  //  Init::quitTTF();
  //  throw "Unable to initialize SDLTTF.";
  //}

  //if (!Init::SDLAudio()) {
  //  Init::quitSDLAudio();
  //  throw "Unable to initialize SDLAudio";
  //}
}

View::~View() {
  //Init::quitTTF();
  //Init::quitSDLAudio();
  //Init::quitSDL();
}

void View::present(std::shared_ptr<Scene> scene) {
  this->scene = scene;
  update();
}

void View::update() {
  bool shouldQuit = false;
  auto gameTimer = GameTimer();
  while (!shouldQuit) {
    gameTimer.startCap();
    SDL_PumpEvents();
    double delta = gameTimer.update();
    const Uint8 *keyState = SDL_GetKeyboardState(nullptr);
    if (keyState[SDL_SCANCODE_ESCAPE]) {
      shouldQuit = true;
    }

    renderer->clear();

    scene->update(delta);
    scene->render(renderer);

    renderer->present();

    gameTimer.capFrameRate();

    //gameTimer->startCap();

    //// control stuff probably
    //SDL_PumpEvents();
    //const Uint8 *keyState = SDL_GetKeyboardState(nullptr);
    //if (keyState[SDL_SCANCODE_ESCAPE]) {
    //  shouldQuit = true;
    //}

    //double delta = gameTimer->update();

    //renderer->clear();

    //scene->update(delta);
    //scene->render(renderer);

    //renderer->present();

    //gameTimer->capFrameRate();
  }
}
