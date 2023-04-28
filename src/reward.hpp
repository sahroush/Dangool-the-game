#pragma once

#include "entity.hpp"

class Reward : public Entity{
public:
    int get_score();
    void set_display(bool val);
    bool get_display();
    void update();
protected:
    int update_count;
    int animation_update_step;
    int img_y;
    int width, height;
    vector < int > img_x;
    int score;
    Vector2f scale;
    void set_frame(int x);
    bool display;
    SoundBuffer collection_sound_buffer;
    Sound collection_sound;
};