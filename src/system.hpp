#pragma once

#include "level.hpp"
#include "simplescreen.hpp"
#include "global_stuff.hpp"

class System{
public:
    System(int width, int height);
    void run();
    ~System();
    RenderWindow window;
private:
    SimpleScreen* game_over_tab;
    SimpleScreen* victory_tab;
    void update();
    void render();
    void handle_events();
    void handle_key_up(Keyboard::Key key);
    void handle_key_down(Keyboard::Key key);
    View view;
    State state;
    Level* levels[LEVEL_COUNT];
    Level* current_level;
    int current_level_id;
    bool is_closed;
    Clock clock;
    Time gameover_duration = seconds(7.9f);
    Time victory_duration = seconds(8.0f);
    Time accumulator = Time::Zero;
};
