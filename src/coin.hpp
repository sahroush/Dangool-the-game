#pragma once

#include "reward.hpp"

namespace coin {
static const int COIN_WIDTH = 11, COIN_HEIGHT = 11;
static const int IMG_Y = 66;
static const vector<int> IMG_X = {2, 18, 34, 50, 34, 18};
static const int ANIMATION_UPDATE_STEP = 12;
static const int SCORE = 5;
static const Vector2f COIN_SCALE = {4, 4};
const int COIN_COLLECTION_SOUND_VOLUME = 30;
} // namespace coin

class Coin : public Reward {
public:
  Coin();
};