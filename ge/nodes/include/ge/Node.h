#pragma once

#include "../../../utils/include/ge/Position.h"
#include "Hashable.h"
#include "Updateable.h"

#include <memory>
#include <string>
#include <vector>

namespace ge {
  class Action;
  class CameraNode;
  class Rect;
  class Scene;
  class Node: public std::enable_shared_from_this<Node>,
              public Updateable,
              public Hashable {
  public:
    Node(const int &width, const int &height);

    int getX();
    int getY();
    void setX(const int &x);
    void setY(const int &y);
    void setXY(const int &x, const int &y);

    void setXScale(const double &scale);
    void setYScale(const double &scale);
    double getXScale();
    double getYScale();
    int getWidth();
    int getHeight();
    Rect getBounds();

    void setAnchorPoint(const double &x, const double &y);

    void setAction(std::shared_ptr<Action> action);
    bool hasAction();

    //updateable
    virtual void update(double delta);

    //hashable
    std::string getUUID() const;
    bool operator==(const Hashable &rhs) const;

    virtual void add(std::shared_ptr<Node> node);
    std::shared_ptr<Node> remove(std::shared_ptr<Node> node);

    virtual void setScene(std::shared_ptr<Scene> scene);

    std::shared_ptr<Node> getParent() const;

    void removeFromParent();

    bool isVisible();

    void setCameraNode(std::shared_ptr<CameraNode> cameraNode);
    std::shared_ptr<CameraNode> getCameraNode() const;

  protected:
    std::vector<std::shared_ptr<Node>> children = {};
    const std::string uuid;
    std::weak_ptr<Scene> scene;
    std::shared_ptr<Action> action;

  private:
    int x = 0;
    int y = 0;

    double anchorX = 0.0;
    double anchorY = 0.0;

    double xScale = 1.0;
    double yScale = 1.0;
    const int width;
    const int height;

    std::weak_ptr<Node> parent;
    std::weak_ptr<CameraNode> cameraNode;
    // why did I add this? probably should be public and control rendering
    bool visible = false;
  };
}
