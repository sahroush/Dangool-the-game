#pragma once

#include "reward.hpp"

namespace star {
static const int STAR_WIDTH = 9, STAR_HEIGHT = 9;
static const int IMG_Y = 52;
static const vector<int> IMG_X = {179, 195, 211, 227, 211, 195};
static const int ANIMATION_UPDATE_STEP = 12;
static const int SCORE = 1;
static const Vector2f STAR_SCALE = {4, 4};
const int STAR_COLLECTION_SOUND_VOLUME = 30;
} // namespace star

class Star : public Reward {
public:
  Star();
};