#include "simplescreen.hpp"

SimpleScreen::SimpleScreen(string message, string music_name, string font_name, int text_size = 50){
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
}