#include "button.hpp"

Button::Button(string message, string font_name, int text_size){
    text.setString(message);
    if (!font.loadFromFile(FONTS_PATH + font_name)){
        throw runtime_error("couldn't load font");
    }
    if(!pressed_texture.loadFromFile(PICS_PATH + "button_pressed.png")){
        throw runtime_error("couldn't load pressed button png");
    }
    if(!depressed_texture.loadFromFile(PICS_PATH + "button_depressed.png")){
        throw runtime_error("couldn't load depressed button png");
    }
    pressed.setTexture(pressed_texture);
    depressed.setTexture(depressed_texture);
    text.setFont(font);
    text.setCharacterSize(text_size);
    text.setColor(Color::White);
    Vector2f scale;
    scale.x = (text.getGlobalBounds().width + 2*button::MARGIN) / pressed.getGlobalBounds().width;
    scale.y = (text.getGlobalBounds().height + 2*button::MARGIN) / pressed.getGlobalBounds().height;
    pressed.setScale(scale);
    scale.x = (text.getGlobalBounds().width + 2*button::MARGIN) / depressed.getGlobalBounds().width;
    scale.y = (text.getGlobalBounds().height + 2*button::MARGIN) / depressed.getGlobalBounds().height;
    depressed.setScale(scale);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(1);
}

void Button::set_position(Vector2f position){
    pos = position;
}   

void Button::render(RenderWindow &window){
    if(is_pressed){
        pressed.setPosition(pos);
        window.draw(pressed);
    }
    else{
        depressed.setPosition(pos);
        window.draw(depressed);
    }
    text.setPosition(pos.x + button::MARGIN, pos.y + button::MARGIN);
    window.draw(text);
}

void Button::toggle(){
    is_pressed = !is_pressed;
}