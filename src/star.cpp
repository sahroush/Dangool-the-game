#include "star.hpp"

Star::Star() {
  if (!texture->loadFromFile(PICS_PATH + "objects.png")) {
    throw runtime_error("couldn't read star sprite");
  }
  if (!collection_sound_buffer.loadFromFile(AUDIO_PATH +
                                            "star_collection_sound.wav"))
    throw runtime_error("couldn't read star collection sound");
  collection_sound.setBuffer(collection_sound_buffer);
  sprite.setTexture(*texture);
  update_count = 0;
  display = true;
  collection_sound.setVolume(star::STAR_COLLECTION_SOUND_VOLUME);
  animation_update_step = star::ANIMATION_UPDATE_STEP;
  img_y = star::IMG_Y;
  img_x = star::IMG_X;
  score = star::SCORE;
  scale = star::STAR_SCALE;
  width = star::STAR_WIDTH;
  height = star::STAR_HEIGHT;
}