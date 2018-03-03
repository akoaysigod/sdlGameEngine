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

  for (auto child: children) {
    auto spriteNode = std::dynamic_pointer_cast<SpriteNode>(child);
    if (spriteNode) {
      renderer->renderCopy(spriteNode->getTexture()->getCPtr(),
                           spriteNode->getTexture()->getClipRect(),
                           spriteNode->getBounds());
    }
  }
}
