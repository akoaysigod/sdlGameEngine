#pragma once

#include "Node.h"
#include "../../../rendering/include/ge/Renderable.h"

namespace ge {
  class CameraNode: public Node, public Renderable {
  public:
    using Node::Node;

    void add(std::shared_ptr<Node> node);
    void render(const std::shared_ptr<Renderer> &renderer);
  };
}
