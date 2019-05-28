#pragma once

#include "Node.h"
#include "../../../rendering/include/ge/Renderable.h"

#include <memory>
#include <optional>

namespace ge {
  class Point;

  class CameraNode: public Node, public Renderable {
  public:
    using Node::Node;

    Point getCenter(const int &x, const int &y);

    void add(std::shared_ptr<Node> node);
    void render(const std::shared_ptr<Renderer> &renderer);

    void follow(const std::shared_ptr<Node> &node);

    void update(double delta);

  private:
    std::optional<std::shared_ptr<Node>> followNode;
  };
}
