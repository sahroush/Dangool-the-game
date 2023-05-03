#include "waypoint.hpp"

Waypoint::Waypoint() {
  if (!texture->loadFromFile(PICS_PATH + "waypoint.png")) {
    throw runtime_error("couldn't read waypoint sprite");
  }
  sprite.setTexture(*texture);
  sprite.setScale(SCALE);
  update_count = 0;
}

void Waypoint::update() {
  update_count++;
  update_count %= waypoint::ANIMATION_UPDATE_STEP;
  if (!update_count)
    rotate90();
}