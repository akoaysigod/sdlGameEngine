#pragma once

#include "../include/Renderable.h"
#include "../include/Updateable.h"

#include <memory>
#include <map>
#include <vector>

namespace ge {
  class Node;
  class Renderer;
  class SpriteNode;

  class Scene: std::enable_shared_from_this<Scene>, public Updateable {
  public:
    //updateable
    virtual void update(double delta);

    void add(std::shared_ptr<SpriteNode> spriteNode);
    void addRenderable(std::shared_ptr<Renderable> renderable);

    std::shared_ptr<Node> remove(std::shared_ptr<Node> node);

    void render(const Renderer &renderer);

    std::vector<std::shared_ptr<Node>> getChildren();

  protected:
    std::vector<std::shared_ptr<Node>> children = {};

  private:
    std::map<int, std::vector<std::shared_ptr<Renderable>>> renderables = {};
    std::vector<int> zPositions = {};
  };
}
