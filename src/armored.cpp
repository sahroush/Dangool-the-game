#include "armored.hpp"

ArmoredEnemy::ArmoredEnemy() {
  if (!texture->loadFromFile(PICS_PATH + "armored.png")) {
    throw runtime_error("couldn't read armored sprite");
  }
  sprite.setTexture(*texture);
  display = true;
  hp = 1;
  vx = 0;
  scale = {4, 4};
  set_frame(frames[cur_frame]);
  score = 10;
  ay = 0.3;
}

bool ArmoredEnemy::is_lethal() { return state != armored_enemy::SLEEPING; }

bool ArmoredEnemy::is_hittable() { return state == armored_enemy::SLEEPING; }

int ArmoredEnemy::calc_frame() {
  update_count++;
  update_count %= FRAME_RATE;
  switch (state) {
  case (armored_enemy::WALKING):
    return walk_frames[(update_count / armored_enemy::ANIMATION_UPDATE_STEP) %
                       walk_frames.size()];
    break;
  case (armored_enemy::SLEEPING):
    return sleep_frames[(update_count / armored_enemy::ANIMATION_UPDATE_STEP) %
                        sleep_frames.size()];
    break;
  case (armored_enemy::GOING_TO_SLEEP):
    return going_to_sleep_frames[(update_count /
                                  armored_enemy::ANIMATION_UPDATE_STEP) %
                                 going_to_sleep_frames.size()];
    break;
  case (armored_enemy::WAKING_UP):
    return waking_up_frames[(update_count /
                             armored_enemy::ANIMATION_UPDATE_STEP) %
                            waking_up_frames.size()];
    break;
  }
}

void ArmoredEnemy::update_avatar() {
  int prev_h = get_height();
  switch (state) {
  case (armored_enemy::WALKING):
    vx = armored_enemy::SPEED * direction;
    accumulator += clock.restart();
    set_frame(frames[cur_frame = calc_frame()], direction < 0);
    if (accumulator >= walking_duration) {
      state = armored_enemy::GOING_TO_SLEEP;
      update_count = 0;
      accumulator = Time::Zero;
    }
    break;
  case (armored_enemy::SLEEPING):
    vx = 0;
    accumulator += clock.restart();
    set_frame(frames[cur_frame = calc_frame()]);
    if (accumulator >= sleeping_duration) {
      state = armored_enemy::WAKING_UP;
      update_count = 0;
      accumulator = Time::Zero;
    }
    draw_external_sprite(
        external_frames[cur_frame].left, external_frames[cur_frame].top,
        external_frames[cur_frame].width, external_frames[cur_frame].height);
    break;
  case (armored_enemy::GOING_TO_SLEEP):
    vx = 0;
    set_frame(frames[cur_frame = calc_frame()], direction < 0);
    if ((update_count / armored_enemy::ANIMATION_UPDATE_STEP) + 1 >=
        (int)going_to_sleep_frames.size()) {
      state = armored_enemy::SLEEPING;
      update_count = 0;
      accumulator = Time::Zero;
    }
    break;
  case (armored_enemy::WAKING_UP):
    vx = 0;
    set_frame(frames[cur_frame = calc_frame()], direction < 0);
    if ((update_count / armored_enemy::ANIMATION_UPDATE_STEP) + 1 >=
        (int)waking_up_frames.size()) {
      state = armored_enemy::WALKING;
      update_count = 0;
      accumulator = Time::Zero;
    }
    break;
  }
  int cur_h = get_height();
  sprite.move(0, prev_h - cur_h);
}

void ArmoredEnemy::update(double left_bound, double right_bound) {
  update_avatar();
  if (state == armored_enemy::WALKING)
    update_position(left_bound, right_bound);
}