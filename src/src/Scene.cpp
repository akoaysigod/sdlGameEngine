#include "../include/Scene.h"

#include "../include/Node.h"
#include "../include/Renderer.h"
#include "../include/SpriteNode.h"

#include <algorithm>

using namespace ge;

//updateable
void Scene::update(double delta) {
  for (auto updateable: children) {
    if (updateable.get()) {
      updateable->update(delta);
    }
  }
}

void Scene::add(std::shared_ptr<SpriteNode> spriteNode) {
  //check already added
  addRenderable(spriteNode);
  children.push_back(spriteNode);
  spriteNode->setScene(this);
}

void Scene::addRenderable(std::shared_ptr<Renderable> renderable) {
  auto zPosition = renderable->zPosition;
  if (renderables.find(zPosition) == renderables.end()) {
    renderables[zPosition] = {renderable};
    zPositions.push_back(zPosition);
    std::sort(zPositions.begin(), zPositions.end());
  }
  else {
    renderables[zPosition].push_back(renderable);
  }
}

std::shared_ptr<Node> Scene::remove(std::shared_ptr<Node> node) {
  auto child = std::find(children.begin(), children.end(), node);
  if (child != children.end()) {
    children.erase(child);
  }

  auto renderable = dynamic_cast<Renderable *>(node.get());
  if (!renderable) {
    if (child->get()) {
      return node;
    }
    return std::shared_ptr<Node>();
  }

  for (auto i: zPositions) {
    for (auto it = this->renderables[i].begin(); it != this->renderables[i].end(); it++) {
      if ((*it).get() == renderable) {
        this->renderables[i].erase(it);
        return node;
      }
    }
  }

  if (child->get()) {
    return node;
  }
  return std::shared_ptr<Node>();
}

std::vector<std::shared_ptr<Node>> Scene::getChildren() {
  return children;
}

void Scene::render(const Renderer &renderer) {
  for (auto i: zPositions) {
    for (auto renderable: renderables[i]) {
      if (renderable.get()) {
        renderable->render(renderer);
      }
    }
  }
}
