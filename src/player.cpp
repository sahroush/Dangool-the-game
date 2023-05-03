#include "player.hpp"

Player::Player(int x_, int y_) {
  skin = player::KING; // we do need a skin picker but fuck off for now :D
  if (!texture->loadFromFile(PICS_PATH + "characters.png")) {
    throw runtime_error("couldn't read player sprite");
  }
  if (!jumping_sound_buffer.loadFromFile(AUDIO_PATH +
                                         "player_jumping_sound.wav"))
    throw runtime_error("couldn't read player jumping sound");
  jumping_sound.setBuffer(jumping_sound_buffer);
  jumping_sound.setVolume(player::JUMP_SOUND_VOLUME);
  if (!screaming_sound_buffer.loadFromFile(AUDIO_PATH + "scream.ogg"))
    throw runtime_error("couldn't read player screaming sound");
  screaming_sound.setBuffer(screaming_sound_buffer);
  if (!kill_sound_buffer.loadFromFile(AUDIO_PATH + "enemy_killed.ogg"))
    throw runtime_error("couldn't read player kill sound");
  kill_sound.setBuffer(kill_sound_buffer);
  hp = 3;
  sprite.setTexture(*texture);
  vx = vy = ax = 0;
  ay = player::GRAVITY;
  going_up = faced_left = going_left = going_right = false;
  update_count = 0;
  state = player::STANDBY;
  scale = player::CHARACTER_SCALE;
  jumping = false;
  sprite.setPosition(x_, y_);
  set_frame(player::IDLE[0]);
}

void Player::update_avatar() {
  update_count++;
  update_count %= FRAME_RATE;
  if (vx < 0 and !faced_left) {
    faced_left = true;
  }
  if (vx > 0 and faced_left) {
    faced_left = false;
    mirror_sprite_horizontally();
  }
  switch (state) {
  case (player::WALKING):
    set_frame(
        player::RUN_FRAMES[(update_count / player::ANIMATION_UPDATE_STEP) %
                           player::RUN_FRAMES.size()]);
    break;
  case (player::STANDBY):
    set_frame(player::IDLE[(update_count / player::ANIMATION_UPDATE_STEP) %
                           player::IDLE.size()]);
    break;
  case (player::CLIMBING):
    set_frame(
        player::CLIMB_FRAMES[(update_count / player::ANIMATION_UPDATE_STEP) %
                             player::CLIMB_FRAMES.size()]);
    break;
  case (player::HANGING):
    set_frame(
        player::CLIMB_IDLE[(update_count / player::ANIMATION_UPDATE_STEP) %
                           player::CLIMB_IDLE.size()]);
    break;
  case (player::JUMPING):
    set_frame(
        player::JUMP_FRAMES[(update_count / player::ANIMATION_UPDATE_STEP) %
                            player::JUMP_FRAMES.size()]);
    break;
  }
}

bool Player::has_stomped(FloatRect enemy) {
  FloatRect me = sprite.getGlobalBounds();
  me = find_first_collision(me, enemy);
  if (check_bottom_collision(me, enemy)) {
    return 1;
  }
  return 0;
}

void Player::handle_walking_on_enemy(FloatRect enemy) {
  FloatRect me = sprite.getGlobalBounds();
  me = find_first_collision(me, enemy);
  if (check_bottom_collision(me, enemy)) {
    vy = -player::JUMP_STRENGTH;
  }
}

void Player::handle_kill() {
  vy = -player::JUMP_STRENGTH;
  kill_sound.play();
  kill_sound.pause();
  kill_sound.setPlayingOffset(seconds(0.3));
  kill_sound.play();
}

void Player::update_state() {
  if (vx == 0 and vy == 0)
    state = player::STANDBY;
  else if (vy != 0)
    state = player::JUMPING;
  else
    state = player::WALKING;
}

void Player::update_sheild() {
  accumulator += clock.restart();
  if (accumulator > immunity_duration)
    sprite.setColor(Color::White);
  else
    sprite.setColor(PURPLE);
}

bool Player::is_immune() {
  accumulator += clock.restart();
  return (accumulator <= immunity_duration);
}

void Player::update(double left_bound, double right_bound) {
  if (jumping)
    jump();
  update_state();
  update_avatar();
  update_position(left_bound, right_bound);
  update_sheild();
}

void Player::go_left() {
  if (going_left)
    return;
  going_left = true;
  vx -= player::SPEED;
}

void Player::go_right() {
  if (going_right)
    return;
  going_right = true;
  vx += player::SPEED;
}

void Player::stop_left() {
  if (!going_left)
    return;
  going_left = false;
  vx += player::SPEED;
}

void Player::stop_right() {
  if (!going_right)
    return;
  going_right = false;
  vx -= player::SPEED;
}

void Player::jump() {
  if (going_up)
    return;
  jumping_sound.play();
  going_up = true;
  jumping = true;
  vy -= player::JUMP_STRENGTH;
  ay = player::GRAVITY;
}

void Player::stop_jump() { jumping = false; }

bool Player::is_going_down() { return vy > 0; }

void Player::fall() {
  if (going_up)
    return;
  ay = player::GRAVITY;
}

int Player::get_hp() { return hp; }

void Player::get_hit() {
  vy = -player::JUMP_STRENGTH;
  hp--;
  accumulator = Time::Zero;
  screaming_sound.play();
}

void Player::set_frame(int frame) {
  auto rect = IntRect(player::IMG_X[frame], player::IMG_Y[skin],
                      player::CHARACTER_WIDTH, player::CHARACTER_HEIGHT);
  rect.left -= player::CHARACTER_WIDTH;
  rect.top -= player::CHARACTER_HEIGHT;
  Entity::set_frame(rect, faced_left);
}