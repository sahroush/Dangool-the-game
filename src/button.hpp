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
private:
    Font font;
    Text text;
    Sprite pressed;
    Sprite depressed;
    Texture pressed_texture;
    Texture depressed_texture;
    bool is_pressed = false;
    Vector2f pos;
};