#include "cherry.hpp"

Cherry::Cherry(){
    if (!texture->loadFromFile(PICS_PATH + "mobs.png")) {
        throw runtime_error("couldn't read mobs sprite");
    }
    sprite.setTexture(*texture);
    display = true;
    vx = 0;
    scale = {3, 3};
    set_frame(frames[0]);
    score = 30;
    ay = cherry::GRAVITY;
    direction = -1;
}

void Cherry::set_initial_pos(Vector2f pos){
    initial_pos = pos;
    sprite.setPosition(pos);
}

bool Cherry::is_hittable(){
    return state == cherry::IDLE;
}

bool Cherry::is_killable(){
    return state == cherry::MOVING;
}

int Cherry::calc_frame(){
    update_count++;
    update_count %= FRAME_RATE;
    switch(state){
        case(cherry::IDLE):
            return idle_frames[(update_count/cherry::ANIMATION_UPDATE_STEP)%idle_frames.size()];
            break;
        case(cherry::KNOCKED):
            return panic_frames[(update_count/cherry::ANIMATION_UPDATE_STEP)%panic_frames.size()];
            break;
        case(cherry::MOVING):
            return move_frames[(update_count/cherry::ANIMATION_UPDATE_STEP)%move_frames.size()];
            break;
    }
}

void Cherry::update_avatar(){
    int prev_h = get_height();
    switch(state){
        case(cherry::MOVING):
            vx = cherry::SPEED * direction;
            set_frame(frames[cur_frame = calc_frame()], direction>0);
            break;
        case(cherry::KNOCKED):
            vx = 0;
            accumulator += clock.restart();
            set_frame(frames[cur_frame = calc_frame()], direction>0);
            if (accumulator >= knock_out_duration){
                state = cherry::IDLE;
                update_count = 0;
                accumulator = Time::Zero;
                sprite.setPosition(initial_pos);
            }
            break;
        case(cherry::IDLE):
            vx = 0;
            set_frame(frames[cur_frame = calc_frame()], direction>0);
            break;
    }
    int cur_h = get_height();
    sprite.move(0, prev_h - cur_h);
}

void Cherry::fall(){
    ay = cherry::GRAVITY;
}

void Cherry::update(double left_bound, double right_bound){
    update_avatar();
    update_position(left_bound, right_bound);
}

void Cherry::be_gone(){
    display = false;
}

void Cherry::get_hit(){
    update_count = 0;
    accumulator = Time::Zero;
    state = cherry::MOVING;
}

void Cherry::get_killed(){
    update_count = 0;
    accumulator = Time::Zero;
    clock.restart();
    state = cherry::KNOCKED;
}