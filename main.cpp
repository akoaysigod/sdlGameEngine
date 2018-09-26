#include "ge/nodes/include/ge/Scene.h"
#include "ge/rendering/include/ge/View.h"
#include "ge/rendering/include/ge/Window.h"

#include <iostream>
#include <memory>

int main(int argc, char** argv){
  auto window = ge::Window("test", 0, 0, 800, 640);
  auto view = ge::View(window, 0, 0 ,0);
  auto scene = std::make_shared<ge::Scene>(800, 640);
  view.present(scene);

	return 0;
}
