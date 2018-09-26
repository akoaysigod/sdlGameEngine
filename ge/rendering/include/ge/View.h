#pragma once

#include <memory>

namespace ge{
  class GameTimer;
  class Renderer;
  class Scene;
  class Window;

  class View {
  public:
    View(const Window &window,
         const int &red,
         const int &green,
         const int &blue);
    ~View();

    void present(std::shared_ptr<Scene> scene);
    void update();

  protected:
    bool shouldUpdateScene = true;

  private:
    const std::unique_ptr<GameTimer> gameTimer;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Renderer> renderer;
  };
}
