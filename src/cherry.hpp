#pragma once

#include "enemy.hpp"

namespace cherry{
    const int ANIMATION_UPDATE_STEP = 24;
    enum State {MOVING, KNOCKED, IDLE};
    const int SPEED = 3;
    const float GRAVITY = 0.3;
}

class Cherry : public Enemy{
public:
    Cherry(Vector2f pos);
    bool is_hittable();
    bool is_killable();
    void update(double left_bound, double right_bound);
    void get_hit();
    void be_gone();
    void get_killed();
    void fall();
private:
    cherry::State state = cherry::IDLE;
    vector <IntRect> frames = {{161, 66, 15, 14}, {130, 61, 14, 16}, {177, 67, 15, 13},
    {114, 57, 14, 19}, {98, 56, 14, 21}, {146, 65, 14, 14}};
    vector < int > idle_frames = {0, 1};
    vector < int > panic_frames = {2, 5};
    vector < int > move_frames = {3, 4};
    int update_count = 0;
    int cur_frame = 0;
    int calc_frame();
    void update_avatar();
    Clock clock;
    Time knock_out_duration = seconds(3.0f);
    Time accumulator = Time::Zero;
    Vector2f initial_pos;
};