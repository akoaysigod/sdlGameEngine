#pragma once

#include <SDL.h>

#include "../../../actions/include/ge/Action.h"
#include "../../../utils/include/ge/Position.h"
#include "Hashable.h"
#include "Updateable.h"

#include <memory>
#include <string>
#include <vector>

namespace ge {
  class Scene;
  class Node: public std::enable_shared_from_this<Node>,
              public Updateable,
              public Hashable {
  public:
    Node();

    int x = 0;
    int y = 0;
    Position getPosition();
    void setPosition(Position position);
    virtual SDL_Rect getBounds();

    void setAction(std::shared_ptr<Action> action);
    bool hasAction();

    //updateable
    virtual void update(double delta);

    //hashable
    std::string getUUID() const;
    bool operator==(const Hashable &rhs) const;

    void add(std::shared_ptr<Node> node);
    std::shared_ptr<Node> remove(std::shared_ptr<Node> node);

    void setScene(std::shared_ptr<Scene> scene);

    std::shared_ptr<Node> getParent() const;

    void removeFromParent();

  protected:
    std::vector<std::shared_ptr<Node>> children;
    const std::string uuid;
    std::weak_ptr<Scene> scene;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Action> action;
  };
}
