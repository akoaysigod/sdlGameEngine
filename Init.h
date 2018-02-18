#pragma once

//this is really just a temporary class until i can figure out
//how to get windows/cmake to build the library correctly
//for some reason it'll build everything in the add_subdirectory
//but it won't build the umbrella library like on mac/linux
//without a source file being added to the add_library step

class Init {
public:
  static bool SDL();
  static bool SDLAudio();
  static bool SDLTTF();

  static void quitSDL();
  static void quitSDLAudio();
  static void quitTTF();
};
