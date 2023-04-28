#pragma once

#include "level.hpp"
#include "global_stuff.hpp"

class System{
public:
    System(int width, int height);
    void run();
    ~System();//TBD
    RenderWindow window;
private:
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
};
