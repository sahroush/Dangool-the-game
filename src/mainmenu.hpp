#pragma once

#include "button.hpp"
#include "global_stuff.hpp"

class MainMenu {
public:
  MainMenu();
  void render(RenderWindow &window);
  void update();
  bool check_start();
  bool check_exit();
  void play();
  void stop();
  void get_clicked(Vector2f pos);
  void get_unclicked(Vector2f pos);

private:
  Button start_button = Button("Start", "score.ttf", 48);
  Button exit_button = Button("Exit", "score.ttf", 60);
  int update_cnt = 0;
  Texture bgs[BG_CNT];
  Sprite bg;
  Music music;
};