#pragma once

#include "button.hpp"
#include "global_stuff.hpp"

class LevelSelect {
public:
  LevelSelect();
  void render(RenderWindow &window);
  void update();
  int check_level();
  bool check_exit();
  void play();
  void stop();
  void get_clicked(Vector2f pos);
  void get_unclicked(Vector2f pos);

private:
  Button exit_button = Button("Return");
  int update_cnt = 0;
  Texture bgs[BG_CNT];
  Sprite bg;
  Music music;
  Button *levels[LEVEL_COUNT];
};