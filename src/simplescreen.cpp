#include "simplescreen.hpp"

SimpleScreen::SimpleScreen(string message, string music_name, string font_name, int text_size){
    text.setString(message);
    if (!font.loadFromFile(FONTS_PATH + font_name)){
        throw runtime_error("couldn't load font");
    }
    if (!music.openFromFile(AUDIO_PATH + music_name)){
        throw runtime_error("couldn't load music");
    }
    music.setLoop(true);
    text.setFont(font);
    text.setCharacterSize(text_size);
    text.setColor(Color::White);
}

void SimpleScreen::update(){
    if(!(music.getStatus() == Music::Playing))
        music.play();
}

void SimpleScreen::render(RenderWindow &window){
    window.setView(View(FloatRect(0.0f, 0.0f, WIDTH, HEIGHT)));
    window.clear(Color::Black);
    text.setPosition((WIDTH - text.getGlobalBounds().width)/2.f, (HEIGHT - text.getGlobalBounds().height)/2.f);
    window.draw(text);
}

void SimpleScreen::stop(){
    music.stop();
}