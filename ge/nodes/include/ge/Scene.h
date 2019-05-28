#pragma once

#include "../../../rendering/include/ge/Renderable.h"
#include "Updateable.h"

#include <memory>
#include <map>
#include <vector>

namespace ge {
  class CameraNode;
  class Node;
  class Point;
  class Renderer;
  class SpriteNode;

  class Scene: public std::enable_shared_from_this<Scene>, public Updateable {
  public:
    Scene(const int &width, const int &height);

    //updateable
    virtual void update(double delta);

    virtual void add(std::shared_ptr<Node> node);
    virtual std::shared_ptr<Node> remove(std::shared_ptr<Node> node);

    void render(const std::shared_ptr<Renderer> &renderer);

    std::vector<std::shared_ptr<Node>> getChildren();

    std::shared_ptr<CameraNode> cameraNode;

    std::shared_ptr<Point> toWorld(const int &x, const int &y);

  protected:
    std::vector<std::shared_ptr<Node>> children = {};

  private:
    std::map<int, std::vector<std::shared_ptr<Renderable>>> renderables = {};
    std::vector<int> zPositions = {};
    void addRenderable(std::shared_ptr<Renderable> renderable);
  };
}
