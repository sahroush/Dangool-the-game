#pragma once

#include "global_stuff.hpp"
#include "player.hpp"
#include "waypoint.hpp"
#include "coin.hpp"
#include "star.hpp"
#include "enemy.hpp"
#include "armored.hpp"

const Vector2f BLOCK_SCALE = {7.f, 7.f};
const float SMALL_MOVEMENT = 0.1;

namespace level{
    const int HEART_WIDTH = 11;
    const int HEART_HEIGHT = 11;
    const int HEART_X = 2;
    const int HEART_Y = 51;
    const Vector2f HEART_SCALE = {5, 5};
}
class Level{
public:
    Level();
    ~Level(); //TBD
    void update();
    void render(RenderWindow &window);
    void init(int level);
    void handle_key_down(Keyboard::Key key);
    void handle_key_up(Keyboard::Key key);
protected:

private:
    Player* player;
    void read_map(string map_path);
    void render_terrain(RenderWindow &window);
    vector <Entity*> terrain;
    vector <Reward*> rewards;
    vector <Enemy*> enemies;
    vector <FloatRect> terrain_bounds;
    Texture block_texture;
    void find_sprite_bounds(const vector<Entity*>& sprites);
    double leftmost_point, rightmost_point, highest_point, lowest_point;
    Waypoint* teleporter;
    View view;
    void add_terrain(vector <string> &lines);
    void add_stuff(vector <string> &lines, int width, int height);
    void adjust_view();
    void check_collisions();
    void check_player_collisions();
    bool will_fall(Sprite sp);
    bool can_go_right(Sprite sp);
    bool can_go_left(Sprite sp);
    int score;
    void render_rewards(RenderWindow &window);
    void update_rewards();
    void render_score(RenderWindow &window);
    void render_hp(RenderWindow &window, int hp);
    void find_terrain_bounds(vector <string> &lines);
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
    void add_terrain_bound(vector <string> &lines, int row, int col, int dx, int dy);
    void check_enemy_collisions(Enemy *enemy);
};