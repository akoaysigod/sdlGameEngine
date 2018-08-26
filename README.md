# Dependencies
SDL2, 2.0.7  
SDL2_image, 2.0.2  
SDL2_ttf, 2.0.14  
SDL2_mixer, 2.0.2  
Note: For MacOS builds I am assuming a brew install SDL2*. For Windows I hardcoded everything.  
Linux: uuid-dev is also required.  
CMake, at least 3.9.0  

C++17, although I think this can be downgraded as I removed all the features
being used, I may add some back in the future though.

Everything was tested using clang 5.0 and Visual Studio 17. Also seems to work fine
with Apple's clang 9+ or whatever the current compiler that ships with XCode is.

# build
```sh
mkdir build
cd build
cmake ..
# if you need to install clang manually I used the following flags for Linux,
# -DCMAKE_CXX_FLAGS=-I/pathTo/clang/include/c++/v1
# -DCMAKE_EXE_LINKER_FLAGS='-L/pathTo/clang/lib -lc++ -lc++experimental'
# for macOS,
# -DCMAKE_CXX_COMPILER=/pathTo/llvm/bin/clang++
make
```

On Windows, Open -> CMake..., hopefully it builds. I try to keep it up to date but
I don't generally develop on Windows machines.

# basic example usage
```c++
#include <SDL.h>
#include <ge/GameTimer.h>
#include <ge/Init.h>
#include <ge/Renderer.h>
#include <ge/Scene.h>
#include <ge/SpriteNode.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void run() {
  // window position (100, 100)
  auto window = ge::Window("window", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);
  // RGB color, will render a black window
  auto renderer = std::make_shared<ge::Renderer>(window, 0, 0, 0);
  auto scene = std::make_shared<ge::Scene>(SCREEN_WIDTH, SCREEN_HEIGHT);
  //second argument is semi-optional
  auto textureLoader = std::make_shared<ge::TextureLoader>(renderer, pathToTextures);
  auto texture = textureLoader->getTextureFrom('./someFolder/texture.png');
  auto sprite = std::make_shared<ge::SpriteNode>(texture);
  scene->add(sprite);

  auto gameTimer = GameTimer();
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
}

int main() {
  if (!Init::SDL()) {
    Init::quitSDL();
    return 1;
  }

  if (!Init::SDLTTF()) {
    Init::quitTTF();
    return 1;
  }

  if (!Init::SDLAudio()) {
    Init::quitSDLAudio();
    return 1;
  }

  run();

  Init::quitTTF();
  Init::quitSDLAudio();
  Init::quitSDL();

  return 0;
}

```

So much boilerplate :(. I will abstract some of this stuff someday.

# Todo
Wrap SDL IO.
Unhardcode SDL for Windows.
Figure out how to compile with CMake on Windows without opening VS.

# Useful snippets
Not directly related to the use of this engine but things I had to do while using it in
a game to get everything to work nicely.

Mostly here so I don't forget these things.

To get Windows to work,
```c++
#ifdef WIN32
#include <Windows.h>
#endif

int main() {}

#ifdef WIN32
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow) {
  return main();
}
#endif
```

To fix apple directories
```c++
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

// https://stackoverflow.com/questions/516200/relative-paths-not-working-in-xcode-c}
#ifdef __APPLE__
void setMacDir() {
  CFBundleRef mainBundle = CFBundleGetMainBundle();
  CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
  char path[PATH_MAX];
  if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX)) {
  // error!
  }
  CFRelease(resourcesURL);

  chdir(path);
  std::cout << "Current Path: " << path << std::endl;
}
#endif

int main() {
  #if __APPLE__
    setMacDir();
  #endif
}
```
