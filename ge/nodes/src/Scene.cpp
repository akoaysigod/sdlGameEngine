#include "../include/ge/Scene.h"

#include "../include/ge/Node.h"
#include "../../rendering/include/ge/Renderer.h"
#include "../include/ge/SpriteNode.h"

#include <algorithm>

using namespace ge;

//updateable
void Scene::update(double delta) {
  for (auto updateable: children) {
    if (updateable) {
      updateable->update(delta);
    }
  }
}

void Scene::add(std::shared_ptr<Node> node) {
  //check already added
  auto renderable = std::dynamic_pointer_cast<Renderable>(node);
  if (renderable) {
    addRenderable(renderable);
  }
  children.push_back(node);
  node->setScene(this);
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

  auto renderable = std::dynamic_pointer_cast<Renderable>(node);
  if (!renderable) {
    if (child != children.end()) {
      return node;
    }
    return nullptr;
  }

  for (auto i: zPositions) {
    auto found = std::find(renderables[i].begin(), renderables[i].end(), renderable);
    if (found != renderables[i].end()) {
      renderables[i].erase(found);
      return node;
    }
  }

  if (child != children.end()) {
    return node;
  }
  return nullptr;
}

std::vector<std::shared_ptr<Node>> Scene::getChildren() {
  return children;
}

void Scene::render(const std::shared_ptr<Renderer> &renderer) {
  for (auto i: zPositions) {
    for (auto renderable: renderables[i]) {
      if (renderable) {
        renderable->render(renderer);
      }
    }
  }
}
