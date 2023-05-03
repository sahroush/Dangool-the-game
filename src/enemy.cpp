#include "enemy.hpp"

void Enemy::reverse() { direction = -direction; }

void Enemy::get_hit() {
  hp--;
  if (hp == 0)
    display = false;
}

int Enemy::get_direction() { return direction; }

bool Enemy::is_moving() { return vx != 0; }

bool Enemy::get_display() { return display; }

int Enemy::get_score() { return score; }

bool Enemy::is_alive() { return hp != 0; }