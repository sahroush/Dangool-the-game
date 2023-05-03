#pragma once

#include "global_stuff.hpp"
#include "level.hpp"
#include "levelselect.hpp"
#include "mainmenu.hpp"
#include "simplescreen.hpp"

enum State {
  IN_GAME,
  PAUSE_MENU,
  MAIN_MENU,
  LEVEL_SELECT,
  VICTORY_SCREEN,
  GAMEOVER_SCREEN,
  CREDITS,
  EXIT
};

class System {
public:
  System(int width, int height);
  void run();
  ~System();
  RenderWindow window;

private:
  SimpleScreen *game_over_tab;
  SimpleScreen *victory_tab;
  SimpleScreen *credits_tab;
  MainMenu mainmenu;
  LevelSelect level_select;
  void update();
  void render();
  void handle_events();
  void handle_key_up(Keyboard::Key key);
  void handle_key_down(Keyboard::Key key);
  View view;
  State state;
  Level *levels[LEVEL_COUNT];
  Level *current_level;
  int current_level_id;
  bool is_closed;
  Clock clock;
  Texture level_screenshot_texture;
  Sprite screenshot;
  Time gameover_duration = seconds(7.9f);
  Time victory_duration = seconds(8.0f);
  Time accumulator = Time::Zero;
  void handle_mouse_press(Event ev);
  void handle_mouse_release(Event ev);
  Button resume_button = Button("Resume", "score.ttf", 31);
  Button main_menu_button = Button("Main Menu", "score.ttf", 25);
  bool changed_state = false;
};
