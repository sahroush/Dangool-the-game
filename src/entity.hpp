#pragma once

#include "global_stuff.hpp"

namespace entity{
    const int BS_STEP_COUNTS = 30;
}

class Entity{
public:
    Entity();
    Entity(string file_name, Vector2f scale_);
    Entity(Texture* tex, Vector2f scale_);
    void render(RenderWindow &window);
    bool collides_with(Sprite other);
    Vector2f get_position(); 
    Vector2f get_center(); 
    void set_position(double x, double y);
    Sprite get_sprite();
    enum Sprite_state {STANDING, MOVING};
    FloatRect get_next_frame_rect(double left_bound, double right_bound);
    void handle_collision(FloatRect block);
    void update_position(double left_bound, double right_bound);
    double get_height();
    double get_width();
    FloatRect get_rect();
protected:
    double vx = 0, vy = 0, ax = 0, ay = 0;
    Sprite sprite, external_sprite;
    bool has_external_sprite = false;
    Texture* texture = new Texture;
    void mirror_sprite_horizontally();
    void rotate90();
    Vector2f scale;
    void set_frame(IntRect frame, bool mirror = 0);
    FloatRect find_first_collision(FloatRect me, FloatRect terrain);
    FloatRect apply_time_to_rect(FloatRect rect, double time);
    bool check_top_collision(FloatRect me, FloatRect block);
    bool check_bottom_collision(FloatRect me, FloatRect block);
    bool check_left_collision(FloatRect me, FloatRect block);
    bool check_right_collision(FloatRect me, FloatRect block);
    bool x_collision = 0, y_collision = 0;
    int x_after_collision = 0, y_after_collision = 0;
    bool going_up = false;
    FloatRect find_overlap_rect(FloatRect rect1, FloatRect rect2);
    void draw_external_sprite(int x, int y, int w, int h);
};