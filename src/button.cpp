#include "button.hpp"

int Button::get_margin() { return 0.2 * text.getGlobalBounds().width; }

Button::Button(string message, string font_name, int text_size) {
  text.setString(message);
  if (!font.loadFromFile(FONTS_PATH + font_name)) {
    throw runtime_error("couldn't load font");
  }
  if (!pressed_texture.loadFromFile(PICS_PATH + "button_pressed.png")) {
    throw runtime_error("couldn't load pressed button png");
  }
  if (!depressed_texture.loadFromFile(PICS_PATH + "button_depressed.png")) {
    throw runtime_error("couldn't load depressed button png");
  }
  pressed.setTexture(pressed_texture);
  depressed.setTexture(depressed_texture);
  text.setFont(font);
  text.setCharacterSize(text_size);
  text.setColor(YELLOW);
  Vector2f scale;
  scale.x = (text.getGlobalBounds().width + 2 * get_margin()) /
            pressed.getGlobalBounds().width;
  scale.y = (text.getGlobalBounds().height + 2 * get_margin()) /
            pressed.getGlobalBounds().height;
  pressed.setScale(scale);
  scale.x = (text.getGlobalBounds().width + 2 * get_margin()) /
            depressed.getGlobalBounds().width;
  scale.y = (text.getGlobalBounds().height + 2 * get_margin()) /
            depressed.getGlobalBounds().height;
  depressed.setScale(scale);
  depressed.setColor(Color(255, 0, 255));
  pressed.setColor(Color(240, 0, 115));
  text.setOutlineColor(Color(64, 64, 64));
  text.setOutlineThickness(1);
  was_pressed = false;
}

void Button::set_position(Vector2f position) { pos = position; }

bool Button::get_status() {
  bool tmp = was_pressed;
  was_pressed = false;
  return tmp;
}

void Button::render(RenderWindow &window) {
  if (is_pressed) {
    pressed.setPosition(pos);
    window.draw(pressed);
  } else {
    depressed.setPosition(pos);
    window.draw(depressed);
  }
  text.setPosition(pos.x + get_margin(), pos.y + get_margin());
  window.draw(text);
}

float Button::get_width() { return pressed.getGlobalBounds().width; }

float Button::get_height() { return pressed.getGlobalBounds().height; }

bool Button::is_in_button(Vector2f position) {
  FloatRect button_rect;
  button_rect.left = pos.x;
  button_rect.top = pos.y;
  button_rect.width = pressed.getGlobalBounds().width;
  button_rect.height = pressed.getGlobalBounds().height;
  return button_rect.contains(position);
}

void Button::toggle() { is_pressed = !is_pressed; }

void Button::get_clicked(Vector2f position) {
  if (is_in_button(position))
    is_pressed = true;
  else if (is_pressed)
    is_pressed = false, was_pressed = true;
}

void Button::get_unclicked(Vector2f position) {
  if (is_in_button(position))
    is_pressed = false, was_pressed = true;
  else if (is_pressed)
    is_pressed = false, was_pressed = true;
}