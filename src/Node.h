#pragma once

#include "Action.h"
#include "Position.h"
#include "Hashable.h"
#include "Updateable.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace ge {
  class Scene;
  class Node: public Updateable, public Hashable {
  public:
    Node();

    int x = 0;
    int y = 0;
    Position getPosition();
    void setPosition(Position position);

    void setAction(std::shared_ptr<Action> action);
    bool hasAction();

    //updateable
    virtual void update(double delta);

    //hashable
    std::string getUUID() const;
    bool operator==(const Hashable &rhs) const;

    void add(std::shared_ptr<Node> node);

    //this should be a shared_ptr but for some reason using
    //shared_from_this in Scene::add is causing a bad_weak_ptr exception
    //even though scene is contained within a shared_ptr
    void setScene(Scene *scene);

  protected:
    std::vector<std::shared_ptr<Node>> children;
    const std::string uuid;
    std::shared_ptr<Scene> scene;

  private:
    std::optional<std::shared_ptr<Action>> action;
  };
}
