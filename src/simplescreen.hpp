#pragma once

#include "global_stuff.hpp"

class SimpleScreen {
public:
  SimpleScreen(string message, string music_name, string font_name,
               int text_size = 50);
  void update();
  void render(RenderWindow &window);
  void stop();

private:
  Music music;
  Font font;
  Text text;
};