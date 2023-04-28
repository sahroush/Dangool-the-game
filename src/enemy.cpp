#include "enemy.hpp"

void Enemy::reverse(){
    mirror_sprite_horizontally();
    vx = -vx;
}

void Enemy::get_hit(){
    hp--;
}

void Enemy::update(){
    sprite.move(vx, 0);
}

bool Enemy::get_display(){
    return display;
}

bool Enemy::is_alive(){
    return hp != 0;
}