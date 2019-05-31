#include "../include/ge/SpriteNode.h"

#include "../../rendering/include/ge/Renderer.h"
#include "../../rendering/include/ge/Texture.h"

using namespace ge;

SpriteNode::SpriteNode(std::shared_ptr<Texture> texture):
  Node::Node(texture->width, texture->height),
  texture(texture) {}

std::shared_ptr<Texture> SpriteNode::getTexture() {
  return texture;
}

void SpriteNode::setTexture(std::shared_ptr<Texture> texture) {
  this->texture = texture;
}

//renderable
void SpriteNode::render(const std::shared_ptr<Renderer> &renderer) {
  if (isVisible()) {
    renderer->renderCopy(texture->getCPtr(), texture->getClipRect(), getBounds());
  }

  // this is repeated in RectNode
  // could make a private RenderableNode they both inherit from
  // and call super here and in RectNode
  // can probably refactor getBounds some how too
  for (auto child: children) {
    if (!child->isVisible()) { continue; }

    auto renderable = std::dynamic_pointer_cast<Renderable>(child);
    if (renderable) {
      renderable->render(renderer);
    }
  }
}
