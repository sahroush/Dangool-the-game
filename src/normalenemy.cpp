#include "normalenemy.hpp"

NormalEnemy::NormalEnemy(){
    if (!texture->loadFromFile(PICS_PATH + "mobs.png")) {
        throw runtime_error("couldn't read mobs sprite");
    }
    sprite.setTexture(*texture);
    display = true;
    hp = 2;
    vx = 0;
    scale = {4, 4};
    set_frame(frames[0]);
    score = 5;
}

bool NormalEnemy::is_hittable(){
    return state != normal_enemy::KNOCKED;
}

int NormalEnemy::calc_frame(){
    update_count++;
    update_count %= FRAME_RATE;
    switch(state){
        case(normal_enemy::KNOCKED):
            return panic_frames[(update_count/normal_enemy::ANIMATION_UPDATE_STEP)%panic_frames.size()];
            break;
        case(normal_enemy::STAGE1):
            return tank_frames[(update_count/normal_enemy::ANIMATION_UPDATE_STEP)%tank_frames.size()];
            break;
        case(normal_enemy::STAGE2):
            return walk_frames[(update_count/normal_enemy::ANIMATION_UPDATE_STEP)%walk_frames.size()];
            break;
    }
}

void NormalEnemy::update_avatar(){
    int prev_h = get_height();
    switch(state){
        case(normal_enemy::STAGE1):
            vx = normal_enemy::TANK_SPEED * direction;
            set_frame(frames[cur_frame = calc_frame()], direction>0);
            break;
        case(normal_enemy::KNOCKED):
            vx = 0;
            accumulator += clock.restart();
            set_frame(frames[cur_frame = calc_frame()], direction<0);
            if (accumulator >= knock_out_duration){
                state = normal_enemy::STAGE2;
                update_count = 0;
                accumulator = Time::Zero;
            }
            break;
        case(normal_enemy::STAGE2):
            vx = normal_enemy::GNOME_SPEED * direction;
            set_frame(frames[cur_frame = calc_frame()], direction<0);
            break;
    }
    int cur_h = get_height();
    sprite.move(0, prev_h - cur_h);
}

void NormalEnemy::update(double left_bound, double right_bound){
    update_avatar();
    update_position(left_bound, right_bound);
}

void NormalEnemy::get_hit(){
    Enemy::get_hit();
    update_count = 0;
    switch(state){
        case(normal_enemy::KNOCKED):
            throw runtime_error("This shouldn't have happened (normalenemy.cpp:71)");
            break;
        case(normal_enemy::STAGE1):
            state = normal_enemy::KNOCKED;
            clock.restart();
            accumulator = Time::Zero;
            sprite.move(sprite.getGlobalBounds().width/2.f, 0);
            break;
        case(normal_enemy::STAGE2):
            //RIP ;'(
            break;
    }
}