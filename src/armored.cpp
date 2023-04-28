#include "armored.hpp"

ArmoredEnemy::ArmoredEnemy(){
    if (!texture->loadFromFile(PICS_PATH + "armored.png")) {
        throw runtime_error("couldn't read armored sprite");
    }
    sprite.setTexture(*texture);
    display = true;
    hp = 1;
    vx = 2;
}