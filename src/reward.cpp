#include "reward.hpp"

void Reward::set_display(bool val) {
  if (display == true and val == false)
    collection_sound.play();
  display = val;
}

bool Reward::get_display() { return display; }

void Reward::set_frame(int x) {
  sprite.setTextureRect(IntRect(x, img_y, width, height));
  sprite.setScale(scale);
}

void Reward::update() {
  update_count++;
  update_count %= FRAME_RATE;
  set_frame(img_x[(update_count / animation_update_step) % img_x.size()]);
}

int Reward::get_score() { return score; }