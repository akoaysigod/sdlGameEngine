#include "../include/ge/SpriteNode.h"

#include "../../rendering/include/ge/Renderer.h"

using namespace ge;

SpriteNode::SpriteNode(std::shared_ptr<Texture> texture): texture(texture) {}

std::shared_ptr<Texture> SpriteNode::getTexture() {
  return texture;
}

void SpriteNode::setTexture(std::shared_ptr<Texture> texture) {
  this->texture = texture;
}

SDL_Rect SpriteNode::getBounds() {
  if (!parent.expired()) {
    auto parentBounds = this->parent.lock()->getBounds();
    int px = parentBounds.x;
    int py = parentBounds.y;
    return texture->getBounds(x + px, y + py);
  }
  return texture->getBounds(x, y);
}

//renderable
void SpriteNode::render(const std::shared_ptr<Renderer> &renderer) {
  renderer->renderCopy(texture->getCPtr(), texture->getClipRect(), getBounds());

  // this is repeated in RectNode
  // could make a private RenderableNode they both inherit from
  // and call super here and in RectNode
  // can probably refactor getBounds some how too
  for (auto child: children) {
    auto renderable = std::dynamic_pointer_cast<Renderable>(child);
    if (renderable) {
      renderable->render(renderer);
    }
  }
}
