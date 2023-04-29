#pragma once

#include "global_stuff.hpp"
#include "entity.hpp"

class Enemy : public Entity{
public:
    void reverse(); 
    void die();
    bool get_display();
    bool is_alive();
    void get_hit();
    virtual void update(double a, double b)=0;
    int get_direction();
    bool is_moving();
    int get_score();
    virtual bool is_hittable();
protected:
    int hp;
    int score;
    bool display;
    int direction = 1;
};