#include "armored.hpp"

ArmoredEnemy::ArmoredEnemy(){
    if (!texture->loadFromFile(PICS_PATH + "armored.png")) {
        throw runtime_error("couldn't read armored sprite");
    }
    sprite.setTexture(*texture);
    display = true;
    hp = 1;
    vx = 0;
    scale = {4, 4};
    set_frame(frames[0]);
    score = 10;
}

void ArmoredEnemy::update_avatar(){
    update_count++;
    update_count %= FRAME_RATE;
    int prev_h = get_height();
    switch(state){
        case(armored_enemy::WALKING):
            vx = armored_enemy::SPEED * direction;
            accumulator += clock.restart();
            set_frame(frames[walk_frames[(update_count/armored_enemy::ANIMATION_UPDATE_STEP)%walk_frames.size()]], vx<0);
            if (accumulator >= walking_duration){
                state = armored_enemy::GOING_TO_SLEEP;
                update_count = 0;
                accumulator = Time::Zero;
            }
            break;
        case(armored_enemy::SLEEPING):
            vx = 0;
            accumulator += clock.restart();
            set_frame(frames[sleep_frames[(update_count/armored_enemy::ANIMATION_UPDATE_STEP)%sleep_frames.size()]]);
            if (accumulator >= sleeping_duration){
                state = armored_enemy::WAKING_UP;
                update_count = 0;
                accumulator = Time::Zero;
            }
            break;
        case(armored_enemy::GOING_TO_SLEEP):
            vx = 0;
            set_frame(frames[going_to_sleep_frames[(update_count/armored_enemy::ANIMATION_UPDATE_STEP)%going_to_sleep_frames.size()]]);
            if((update_count/armored_enemy::ANIMATION_UPDATE_STEP)+1 >= (int)going_to_sleep_frames.size()){
                state = armored_enemy::SLEEPING;
                update_count = 0;
                accumulator = Time::Zero;
            }
            break;
        case(armored_enemy::WAKING_UP):
            vx = 0;
            set_frame(frames[waking_up_frames[(update_count/armored_enemy::ANIMATION_UPDATE_STEP)%waking_up_frames.size()]]);
            if((update_count/armored_enemy::ANIMATION_UPDATE_STEP)+1 >= (int)waking_up_frames.size()){
                state = armored_enemy::WALKING;
                update_count = 0;
                accumulator = Time::Zero;
            }
            break;
    }
    int cur_h = get_height();
    sprite.move(0, prev_h - cur_h);
}

void ArmoredEnemy::update(double left_bound, double right_bound){
    update_avatar();
    if(state == armored_enemy::WALKING)
        update_position(left_bound, right_bound);
}