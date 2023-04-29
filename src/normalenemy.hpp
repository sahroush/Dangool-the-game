#pragma once

#include "enemy.hpp"

namespace normal_enemy{
    const int ANIMATION_UPDATE_STEP = 12;
    enum State {STAGE1, KNOCKED, STAGE2};
    const int SPEED = 2;
}

class NormalEnemy : public Enemy{
public:
    NormalEnemy();
    bool is_hittable();
    void update(double left_bound, double right_bound);
    void get_hit();
private:
    normal_enemy::State state = normal_enemy::STAGE1;
    vector <IntRect> frames = {{2, 69, 28, 27}, {34, 69, 28, 27}, {97, 82, 12, 13},
    {66, 83, 11, 13}, {82, 82, 11, 14}};
    vector < int > tank_frames = {0, 1};
    vector < int > panic_frames = {2, 3};
    vector < int > walk_frames = {3, 4};
    int update_count = 0;
    int cur_frame = 0;
    int calc_frame();
    void update_avatar();
    Clock clock;
    Time knock_out_duration = seconds(2.0f);
    Time accumulator = Time::Zero;

};