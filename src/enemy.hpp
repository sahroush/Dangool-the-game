#pragma once

#include "global_stuff.hpp"
#include "entity.hpp"

class Enemy : public Entity{
public:
    void update();
    void reverse(); 
    void die();
    bool get_display();
    bool is_alive();
    void get_hit();
protected:
    int hp;
    bool display;
};