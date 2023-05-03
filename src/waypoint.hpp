#pragma once

#include "entity.hpp"

static const Vector2f SCALE = {8 / 11.f, 8 / 11.f};

namespace waypoint {
const int ANIMATION_UPDATE_STEP = 12;
}

class Waypoint : public Entity {
public:
  Waypoint();
  void update();

protected:
private:
  int update_count;
};
