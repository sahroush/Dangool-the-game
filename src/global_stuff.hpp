#pragma once

#include <iostream>
#include <stdexcept>
#include <utility> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <deque>
#include <vector>
#include <chrono>
#include <math.h> 
#include <random>
#include <string>
#include <fstream>

using namespace sf;
using namespace std;

const float PI = acos(-1);
const int WIDTH = 1200;
const int HEIGHT = 850;
const int FRAME_RATE = 72;
const int LEVEL_COUNT = 4;
enum State {IN_GAME, PAUSE_MENU, MAIN_MENU, LEVEL_SELECT, VICTORY_SCREEN, GAMEOVER_SCREEN, CREDITS};
const string PICS_PATH = "./files/pics/", MAPS_PATH = "./files/maps/", AUDIO_PATH = "./files/audio/",
    FONTS_PATH = "./files/fonts/";
const Color BLUE = Color(50, 115, 220);
const Color PURPLE = Color(130, 50, 220);
const Color YELLOW = Color(255, 221, 0);

#define debug(x) cout << x << endl, exit(0);