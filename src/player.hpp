#pragma once

#include "entity.hpp"

namespace player{
    const int JUMP_SOUND_VOLUME = 30;
    static const int IMG_Y[] = {31, 63, 95};
    static const int IMG_X[] = {23, 55, 87, 120, 151, 183, 215, 248, 279, 310, 343, 375,
    407, 439, 471, 503, 535, 567, 598, 630, 662, 694, 727};
    const int ANIMATION_UPDATE_STEP = 12;
    static const int CHARACTER_WIDTH = 15, CHARACTER_HEIGHT = 22;
    enum Skin {NAKED, KING, SOLDIER};
    static const Vector2f CHARACTER_SCALE = {3, 3};
    static const vector < int > WALK_FRAMES = {0, 1, 2, 3},
        JUMP_FRAMES = {4, 5, 6, 7},
        HIT_FRAMES = {8, 9, 8},
        SLASH_FRAMES = {11, 10, 11, 12},
        PUNCH_FRAMES = {11, 13, 11},
        RUN_FRAMES = {14, 15, 16, 17},
        CLIMB_FRAMES = {18, 19, 20, 21},
        CLIMB_IDLE = {21},
        IDLE = {0};
    enum Player_state {WALKING, STANDBY, CLIMBING, HANGING, JUMPING};
    const int SPEED = 5;
    const float GRAVITY = 0.3;
    const int JUMP_STRENGTH = 13;
    const float COLLISION_ERROR = 5;
}
class Player : public Entity{
public:
    Player(int x_, int y_);
    void update(double left_bound, double right_bound);
    void go_left();
    void go_right();
    void stop_left();
    void stop_right();
    void jump();
    bool is_going_down();
    void fall();
    int get_hp();
    void get_hit();
    void stop_jump();
    bool has_hit_enemy(FloatRect enemy);
    void handle_kill();
    bool is_immune();
protected:
    
private:
    player::Skin skin;
    int hp;
    bool faced_left, going_left, going_right;
    bool jumping;
    int update_count;
    player::Player_state state;
    SoundBuffer jumping_sound_buffer;
    Sound jumping_sound;
    SoundBuffer screaming_sound_buffer;
    Sound screaming_sound;
    SoundBuffer kill_sound_buffer;
    Sound kill_sound;
    void update_avatar();
    void update_state();
    void set_frame(int frame);
    Clock clock;
    Time immunity_duration = seconds(3.0f);
    Time accumulator = immunity_duration + seconds(2);
    void update_sheild();
};