#pragma once

#include "enemy.hpp"

namespace normal_enemy{
    const int ANIMATION_UPDATE_STEP = 12;
    enum State {WALKING, KNOCKED};
    const int SPEED = 2;
}

class NormalEnemy : public Enemy{
public:
    NormalEnemy();
    bool is_hittable();
    void update(double left_bound, double right_bound);
private:
    normal_enemy::State state = normal_enemy::WALKING;
    vector <IntRect> frames = {};
    int update_count = 0;
    int cur_frame = 0;
    Clock clock;
    Time knock_out_duration = seconds(2.0f);
    Time accumulator = Time::Zero;

};