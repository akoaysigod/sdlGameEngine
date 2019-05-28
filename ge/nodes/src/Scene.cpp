#include "../include/ge/Scene.h"

#include "../include/ge/CameraNode.h"
#include "../include/ge/Node.h"
#include "../../rendering/include/ge/Renderer.h"
#include "../../utils/include/ge/Point.h"
#include "../include/ge/SpriteNode.h"

#include <algorithm>

using namespace ge;

Scene::Scene(const int &width, const int &height):
  cameraNode(std::make_shared<CameraNode>(width, height)) {
  // this is probably fine?
  addRenderable(cameraNode);
}

std::shared_ptr<Point> Scene::toWorld(const int &x, const int &y) {
  return std::make_shared<Point>(x + cameraNode->getX(), y + cameraNode->getY());
}

//updateable
void Scene::update(double delta) {
  for (auto updateable: children) {
    if (updateable) {
      updateable->update(delta);
    }
  }
  cameraNode->update(delta);
}

void Scene::add(std::shared_ptr<Node> node) {
  //check already added
  auto renderable = std::dynamic_pointer_cast<Renderable>(node);
  if (renderable) {
    addRenderable(renderable);
  }
  children.push_back(node);
  node->setScene(shared_from_this());
  node->setCameraNode(cameraNode);
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
