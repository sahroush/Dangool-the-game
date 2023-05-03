#pragma once

#include "global_stuff.hpp"

namespace button{
    const int MARGIN = 10;
}

class Button{
public:
    Button(string message, string font_name = "score.ttf", int text_size = 25);
    void render(RenderWindow &window);
    void toggle();
    void set_position(Vector2f position);
    bool get_status();
    void get_clicked(Vector2f position);
    void get_unclicked(Vector2f position);
    float get_width();
    float get_height();
private:
    bool is_in_button(Vector2f position);
    Font font;
    Text text;
    Sprite pressed;
    Sprite depressed;
    Texture pressed_texture;
    Texture depressed_texture;
    bool is_pressed = false;
    Vector2f pos;
    bool was_pressed;
};