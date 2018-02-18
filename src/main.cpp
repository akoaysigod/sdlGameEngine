//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
//#include <SDL_ttf.h>
//#include <iostream>
//#include "GameTimer.h"
//#include "MoveAction.h"
//#include "SpriteAtlas.h"
//#include "SpriteNode.h"
//#include "SDLSmartPointerHelper.h"
//#include "Renderer.h"
//#include "Scene.h"
//#include "Texture.h"
//#include "Window.h"

//#pragma clang diagnostic ignored "-Wdocumentation"

//using namespace ge;

//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = 600;

//void logError(const std::string &message) {
//  std::cout << message << " " << SDL_GetError() << std::endl;
//}

//#undef main
//int main(int argc, const char * argv[]) {
//  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//    std::cout << SDL_GetError() << std::endl;
//    SDL_Quit();
//    return 1;
//  }

//  if (TTF_Init()) {
//    logError("TTF failed to init");
//    return 1;
//  }

//  TTF_Quit();
//  SDL_Quit();

//  return 0;
//}
