#include "../include/ge/View.h"
#include "../../utils/include/ge/GameTimer.h"
#include "../../init/include/ge/Init.h"
#include "../include/ge/Renderer.h"
#include "../../nodes/include/ge/Scene.h"

using namespace ge;

View::View(const Window &window,
           const int &red,
           const int &green,
           const int &blue):
  gameTimer(std::make_unique<GameTimer>()),
  renderer(std::make_shared<Renderer>(window, red, green, blue))
{
  if (!Init::SDL()) {
    Init::quitSDL();
    throw "Unable to initialize SDL.";
  }

  if (!Init::SDLTTF()) {
    Init::quitTTF();
    throw "Unable to initialize SDLTTF.";
  }

  if (!Init::SDLAudio()) {
    Init::quitSDLAudio();
    throw "Unable to initialize SDLAudio";
  }
}

View::~View() {
  Init::quitTTF();
  Init::quitSDLAudio();
  Init::quitSDL();
}

void View::present(std::shared_ptr<Scene> scene) {
  this->scene = scene;
  update();
}

void View::update() {
  while (shouldUpdateScene) {
    gameTimer->startCap();
    // control stuff probably

    double delta = gameTimer->update();

    renderer->clear();

    scene->update(delta);
    scene->render(renderer);

    renderer->present();

    gameTimer->capFrameRate();
  }
}
