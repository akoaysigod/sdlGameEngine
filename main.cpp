#include <SDL.h>
#include "ge/utils/include/ge/GameTimer.h"
#include "ge/init/include/ge/Init.h"
#include "ge/nodes/include/ge/Scene.h"
#include "ge/nodes/include/ge/SpriteNode.h"
#include "ge/rendering/include/ge/Renderer.h"
#include "ge/rendering/include/ge/Texture.h"
#include "ge/rendering/include/ge/View.h"
#include "ge/rendering/include/ge/Window.h"

#include "ge/luaBindings/include/ge/InitLua.h"

#include <iostream>
#include <memory>

void test() {
  auto window = ge::Window("test", 0, 0, 800, 640);
  //auto view = ge::View(window, 0, 0 ,0);
  auto renderer = std::make_shared<ge::Renderer>(window, 0, 0, 0);
  auto scene = std::make_shared<ge::Scene>(800, 640);
  auto texture = ge::Texture::init(renderer, "./sprite.jpg");
  auto sprite = std::make_shared<ge::SpriteNode>(texture);
  scene->add(sprite);

  auto gameTimer = ge::GameTimer();
  auto shouldQuit = false;
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
  }
  //view.present(scene);
}

int main(int argc, char** argv){
  if (!ge::Init::SDL()) {
    ge::Init::quitSDL();
    return 1;
  }

  if (!ge::Init::SDLTTF()) {
    ge::Init::quitTTF();
    return 1;
  }

  if (!ge::Init::SDLAudio()) {
    ge::Init::quitSDLAudio();
    return 1;
  }

  if (argc > 1) {
    auto lua = ge::InitLua();
    lua.registerObjects();
    lua.runScript(argv[1]);
  }
  else {
    test();
  }


  ge::Init::quitTTF();
  ge::Init::quitSDLAudio();
  ge::Init::quitSDL();

	return 0;
}
