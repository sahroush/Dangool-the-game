#include "coin.hpp"

Coin::Coin(){
    if (!texture->loadFromFile(PICS_PATH + "objects.png")) {
        throw runtime_error("couldn't read coin sprite");
    }
    if(!collection_sound_buffer.loadFromFile(AUDIO_PATH + "coin_collection_sound.wav"))
        throw runtime_error("couldn't read coin collection sound");
    collection_sound.setBuffer(collection_sound_buffer);
    sprite.setTexture(*texture);
    update_count = 0;
    display = true;
    collection_sound.setVolume(coin::COIN_COLLECTION_SOUND_VOLUME);
    animation_update_step = coin::ANIMATION_UPDATE_STEP;
    img_y = coin::IMG_Y;
    img_x = coin::IMG_X;
    score = coin::SCORE;
    scale = coin::COIN_SCALE;
    width = coin::COIN_WIDTH;
    height = coin::COIN_HEIGHT;
}