#pragma once

#include "global_stuff.hpp"
#include "player.hpp"
#include "waypoint.hpp"
#include "coin.hpp"
#include "star.hpp"
#include "enemy.hpp"
#include "armored.hpp"
#include "normalenemy.hpp"
#include "cherry.hpp"
#include "button.hpp"

const Vector2f BLOCK_SCALE = {7.f, 7.f};
const Vector2f COMPASS_SCALE = {3.f, 3.f};
const int BLOCK_WIDTH = 11, BLOCK_HEIGHT = 11;
const float SMALL_MOVEMENT = 1.1;

namespace level{
    const int HEART_WIDTH = 11;
    const int HEART_HEIGHT = 11;
    const int HEART_X = 2;
    const int HEART_Y = 51;
    const Vector2f HEART_SCALE = {5, 5};
    const int MARGIN = 100;
}
class Level{
public:
    Level();
    ~Level(); 
    void update();
    void render(RenderWindow &window, bool draw_pause = true);
    void init(int level);
    void handle_key_down(Keyboard::Key key);
    void handle_key_up(Keyboard::Key key);
    bool check_lost();
    bool check_won();
    void handle_mouse_press(Vector2f pos);
    void handle_mouse_release(Vector2f pos);
    bool check_paused();
    void unpause();
    void pause();  
    Texture get_screenshot(RenderWindow &window);
protected:

private:
    bool is_paused = false;
    Player* player;
    Button pause_button = Button("Pause");
    void check_enemy_interactions();
    void read_map(string map_path);
    void render_terrain(RenderWindow &window);
    vector <Entity*> terrain;
    vector <Reward*> rewards;
    vector <Enemy*> enemies;
    vector <Cherry*> cherries;
    vector <FloatRect> terrain_bounds;
    Entity* compass;
    Texture block_texture;
    void find_sprite_bounds(const vector<Entity*>& sprites);
    double leftmost_point, rightmost_point, highest_point, lowest_point;
    Waypoint* teleporter;
    View view;
    int remaining_cherry_count = 0;
    void add_terrain();
    void add_stuff(int width, int height);
    void adjust_view();
    void check_collisions();
    void check_player_collisions();
    bool will_fall(Sprite sp);
    bool can_go_right(Sprite sp);
    bool can_go_left(Sprite sp);
    bool has_lost = false;
    bool has_won = false;
    int score;
    void render_rewards(RenderWindow &window);
    void update_rewards();
    void render_score(RenderWindow &window);
    void render_hp(RenderWindow &window, int hp);
    void find_terrain_bounds();
    Font score_font;
    Text score_text;
    Texture heart_texture;
    Sprite* heart_sprite;
    void init_heart();
    void init_music(int id = -1);
    void update_music();
    void render_enemies(RenderWindow &window);
    void update_enemies();
    Music music;
    void add_terrain_bound(int row, int col, int dx, int dy);
    void check_enemy_collisions(Enemy *enemy);
    void activate_gameover_mode();
    void activate_victory_mode();
    void render_cherries(RenderWindow &window);
    void check_cherry_interactions();
    void check_cherry_collisions(Cherry* cherry);
    void update_cherries();
    bool is_terrain(int x, int y);
    vector <string> lines;
    vector <IntRect> terrain_frames = {};
    IntRect get_block_frame(int x, int y); 
    SoundBuffer portal_sound_buffer;
    Sound portal_sound; 
    void init_compass();
    void update_compass();
    void render_compass(RenderWindow &window);
    Vector2f get_local_pos(Vector2f pos);
};

