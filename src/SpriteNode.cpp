#include "SpriteNode.h"

#include "Renderer.h"

using namespace ge;

SpriteNode::SpriteNode(std::shared_ptr<Texture> texture): texture(texture) {}

std::shared_ptr<Texture> SpriteNode::getTexture() {
  return texture;
}

void SpriteNode::setTexture(std::shared_ptr<Texture> texture) {
  this->texture = texture;
}

SDL_Rect SpriteNode::getBounds() {
  return texture->getBounds(x, y);
}

//renderable
void SpriteNode::render(const Renderer &renderer) {
  renderer.renderCopy(texture->getCPtr(), texture->getClipRect(), getBounds());

  for (auto child: children) {
    auto node = child.get();
    auto spriteNode = dynamic_cast<SpriteNode *>(node);
    if (spriteNode != nullptr) {
      auto bounds = spriteNode->getBounds();
      bounds.x += x;
      bounds.y += y;

      renderer.renderCopy(spriteNode->getTexture()->getCPtr(),
                          spriteNode->getTexture()->getClipRect(),
                          bounds);
    }
  }
}

// hashable
bool SpriteNode::operator==(const Hashable &rhs) const {
  return this->getUUID() == rhs.getUUID();
}

std::string SpriteNode::getUUID() const {
  return uuid;
}
