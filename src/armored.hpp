#pragma once

#include "enemy.hpp"

namespace armored_enemy{
    const int ANIMATION_UPDATE_STEP = 12;
    enum State {WALKING, GOING_TO_SLEEP, SLEEPING, WAKING_UP};
    const int SPEED = 2;
}

class ArmoredEnemy : public Enemy{
public:
    ArmoredEnemy();
    bool is_hittable();
    void update(double left_bound, double right_bound);
private:
    armored_enemy::State state = armored_enemy::WAKING_UP;
    vector <IntRect> frames = {{10, 69, 13, 24}, {42, 70, 13, 24}, {74, 69, 13, 24}, {106, 70, 13, 24},
    {137, 11, 16, 19}, {137, 43, 16, 19}, {137, 75, 16, 19}, {137, 108, 16, 19},
    {163, 72, 20, 24}, {163, 41, 21, 20}, {165, 11, 20, 18}};
    vector <IntRect> external_frames = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
    {-5, -5, 12, 5}, {-5, -5, 12, 5}, {-5, -5, 12, 5}, {-5, -5, 12, 5},
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    vector <int> walk_frames = {0, 1, 2, 3, 2, 1};
    vector <int> sleep_frames = {4, 5, 6, 7};
    vector <int> going_to_sleep_frames = {8, 9, 10};
    vector <int> waking_up_frames = {10, 9, 8};
    int calc_frame();
    int update_count = 0;
    int cur_frame = 0;
    void update_avatar();
    Clock clock;
    Time sleeping_duration = seconds(3.0f);
    Time walking_duration = seconds(5.0f);
    Time accumulator = Time::Zero;

};