# to compile this shit on linux with a custom clang install
# alias cmakeBuild="cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. -DCMAKE_CXX_FLAGS=-I/home/tony/.bin/clang/include/c++/v1 -DCMAKE_EXE_LINKER_FLAGS='-L/home/tony/.bin/clang/lib -lc++'"

cmake_minimum_required(VERSION 3.9.0)

project(sdl-game-engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(EXECUTABLE_OUTPUT_PATH .)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(MAC_INCLUDE_DIR /usr/local/include/SDL2)
set(LINUX_INCLUDE_DIR /usr/include/SDL2)
set(WINDOWS_SDL_INCLUDE_DIR "G:/SDL2-2.0.7/include")
set(WINDOWS_SDL_IMAGE_INCLUDE_DIR "G:/SDL2_image-2.0.2/include")
set(WINDOWS_SDL_TTF_INCLUDE_DIR "G:/SDL2_ttf-2.0.14/include")
set(WINDOWS_SDL_MIXER_INCLUDE_DIR "G:/SDL2_mixer-2.0.2/include")

find_path(
  SDL_INCLUDE_DIR
  NAMES SDL.h
  PATHS ${MAC_LIB_DIR} ${LINUX_LIB_DIR} ${WINDOWS_SDL_INCLUDE_DIR}
  PATH_SUFFIXES Headers SDL2
)

find_path(
  SDL_IMAGE_INCLUDE_DIR
  NAMES SDL_image.h
  PATHS ${MAC_INCLUDE_DIR} ${LINUX_LIB_DIR} ${WINDOWS_SDL_IMAGE_INCLUDE_DIR}
  PATH_SUFFIXES Headers SDL2
)

find_path(
  SDL_TTF_INCLUDE_DIR
  NAMES SDL_ttf.h
  PATHS ${MAC_INCLUDE_DIR} ${LINUX_INCLUDE_DIR} ${WINDOWS_SDL_TTF_INCLUDE_DIR}
  PATH_SUFFIXES Headers SDL2
)

find_path(
  SDL_MIXER_INCLUDE_DIR
  NAMES SDL_mixer.h
  PATHS ${MAC_INCLUDE_DIR} ${LINUX_LIB_DIR} ${WINDOWS_SDL_MIXER_INCLUDE_DIR}
  PATH_SUFFIXES Headers SDL2
)

add_subdirectory(ge/)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${PROJECT_NAME} m.cpp)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${SDL_INCLUDE_DIR}
  PRIVATE ${SDL_IMAGE_INCLUDE_DIR}
  PRIVATE ${SDL_TTF_INCLUDE_DIR}
  PRIVATE ${SDL_MIXER_INCLUDE_DIR}
)

if (APPLE)
	find_library(CFLIB CoreFoundation)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${CFLIB})
elseif (UNIX)
  # sudo apt-get install uuid-dev
  find_package(libuuid REQUIRED)
  include_directories(${LIBUUID_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBUUID_LIBRARY})
endif()

set(MAC_LIB_DIR /usr/local/lib/)
set(LINUX_LIB_DIR /usr/lib/x86_64-linux-gnu)
set(WINDOWS_SDL_LIB_DIR "G:/SDL2-2.0.7/lib/x86")
set(WINDOWS_SDL_IMAGE_LIB_DIR "G:/SDL2_image-2.0.2/lib/x86")
set(WINDOWS_SDL_TTF_LIB_DIR "G:/SDL2_ttf-2.0.14/lib/x86")
set(WINDOWS_SDL_MIXER_LIB_DIR "G:/SDL2_mixer-2.0.2/lib/x86")

find_library(
  SDL_LIBRARY
  NAMES SDL2
  PATHS ${MAC_LIB_DIR} ${LINUX_LIB_DIR} ${WINDOWS_SDL_LIB_DIR}
)

find_library(
  SDL_IMAGE_LIBRARY
  NAMES SDL2_image
  PATHS ${MAC_LIB_DIR} ${LINUX_LIB_DIR} ${WINDOWS_SDL_IMAGE_LIB_DIR}
)

find_library(
  SDL_TTF_LIBRARY
  NAMES SDL2_ttf
  PATHS ${MAC_LIB_DIR} ${LINUX_LIB_DIR} ${WINDOWS_SDL_TTF_LIB_DIR}
)

find_library(
  SDL_MIXER_LIBRARY
  NAMES SDL2_mixer
  PATHS ${MAC_LIB_DIR} ${LINUX_LIB_DIR} ${WINDOWS_SDL_MIXER_LIB_DIR}
)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC ${SDL_LIBRARY}
  PRIVATE ${SDL_IMAGE_LIBRARY}
  PRIVATE ${SDL_TTF_LIBRARY}
  PRIVATE ${SDL_MIXER_LIBRARY}
  PUBLIC actions
  PUBLIC nodes
  PUBLIC rendering
  PUBLIC utils
)
