#include <SDL.h>
#include "ge/utils/include/ge/GameTimer.h"
#include "ge/init/include/ge/Init.h"
#include "ge/nodes/include/ge/Scene.h"
#include "ge/rendering/include/ge/Renderer.h"
#include "ge/rendering/include/ge/View.h"
#include "ge/rendering/include/ge/Window.h"

#include "ge/luaBindings/include/ge/InitLua.h"

#include <iostream>
#include <memory>

void test() {
  auto window = ge::Window("test", 0, 0, 800, 640);
  auto view = ge::View(window, 0, 0 ,0);
  auto scene = std::make_shared<ge::Scene>(800, 640);

  view.present(scene);
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

  auto lua = ge::InitLua();
  lua.registerObjects();
  lua.runScript(argv[1]);


  ge::Init::quitTTF();
  ge::Init::quitSDLAudio();
  ge::Init::quitSDL();

	return 0;
}
