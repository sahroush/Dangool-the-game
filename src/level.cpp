#include "level.hpp"


Level::Level(){
    if (!block_texture.loadFromFile(PICS_PATH + "block.png")) {
        throw runtime_error("couldn't read block.png");
    }//TBD: add second block, suitable for stacking
    if (!heart_texture.loadFromFile(PICS_PATH + "objects.png")) {
        throw runtime_error("couldn't read objects.png");
    }
    if (!score_font.loadFromFile(FONTS_PATH + "score.ttf")) {
        throw runtime_error("Could not load score font");
    }
    view = View(FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));
    score = 0;
    score_text.setFont(score_font);
    score_text.setCharacterSize(32);
    init_heart();
    init_music();
}

Level::~Level(){
    music.stop();
    delete player;
    for(auto x : terrain)
        delete x;
    for(auto x : rewards)
        delete x;
    delete heart_sprite;
    delete teleporter;
}

void Level::init_music(int id){
    if(!music.openFromFile(AUDIO_PATH + "music.ogg")){
        throw runtime_error("couldn't open track " + to_string(id));
    }
    music.setLoop(true);
}

void Level::check_player_collisions(){
    FloatRect nex = player->get_next_frame_rect(leftmost_point, rightmost_point);
    for(auto bound : terrain_bounds)
        if(nex.intersects(bound))
            player->handle_collision(bound);
}

void Level::check_collisions(){
    check_player_collisions();
}

bool Level::will_fall(Sprite sp){
    sp.move(0, SMALL_MOVEMENT);
    for(Entity* tr : terrain)
        if(sp.getGlobalBounds().intersects(tr->get_rect()))
            return 0;
    return 1;
}

bool Level::can_go_left(Sprite sp){
    sp.move(-SMALL_MOVEMENT, 0);
    for(Entity* tr : terrain)
        if(sp.getGlobalBounds().intersects(tr->get_rect()))
            return 0;
    return 1;
}

void Level::update_music(){
    if(!(music.getStatus() == Music::Playing))
        music.play();
}

bool Level::can_go_right(Sprite sp){
    sp.move(SMALL_MOVEMENT, 0);
    for(Entity* tr : terrain)
        if(sp.getGlobalBounds().intersects(tr->get_rect()))
            return 0;
    return 1;
}

void Level::update(){
    if(will_fall(player->get_sprite())){
        player->fall();
    }
    check_collisions();
    player->update(leftmost_point, rightmost_point);
    update_rewards();
    teleporter->update();
    update_music();
    update_enemies();
}

void Level::update_rewards(){
    for(Reward* r : rewards){
        if(r->get_display()){
            r->update();
            if(player->collides_with(r->get_sprite())){
                score += r->get_score();
                r->set_display(false);
            }
        }
    }
}   

void Level::update_enemies(){
    for(Enemy* e : enemies){
        if(e->is_alive()){
            e->update();
            if(player->collides_with(e->get_sprite())){
                //do stoopid shit here
            }
        }
    }
}   

void Level::render_rewards(RenderWindow &window){
    for(Reward* r : rewards)
        if(r->get_display())
            r->render(window);
}

void Level::render_enemies(RenderWindow &window){
    for(Enemy* e : enemies)
        if(e->get_display())
            e->render(window);
}

void Level::render_score(RenderWindow &window){
    score_text.setString("Score: " + to_string(score));
    score_text.setOutlineColor(Color::White);
    score_text.setOutlineThickness(2);
    score_text.setColor(Color(153, 0, 145));
    score_text.setPosition(view.getCenter().x - view.getSize().x/2.f+5, view.getCenter().y - view.getSize().y/2.f+5);
    window.draw(score_text);
}

void Level::render_hp(RenderWindow &window, int hp){
    heart_sprite->setPosition(score_text.getGlobalBounds().left,
     score_text.getGlobalBounds().top + score_text.getGlobalBounds().height);   
    for(int i = 0 ; i < hp ; i ++){
        window.draw(*heart_sprite);
        heart_sprite->move(heart_sprite->getGlobalBounds().width, 0);
    }
}

void Level::render(RenderWindow &window){
    teleporter->render(window);
    render_terrain(window);
    player->render(window);
    render_rewards(window);
    adjust_view();
    window.setView(view);
    render_score(window);
    render_hp(window, player->get_hp());
    render_enemies(window);
}

void Level::render_terrain(RenderWindow &window){
    for(Entity* tr : terrain)
        tr->render(window);
}

void Level::add_terrain_bound(vector <string> &lines, int row, int col, int dx, int dy){
    FloatRect res(col*dx, row*dy, dx, 0);
    for(int i = row ; i < (int)lines.size() ; i ++){
        if(int(lines[i].size()) > col and lines[i][col] == '.')
            res.height += dy;
        else
            break;
    }
    terrain_bounds.push_back(res);
}

void Level::find_terrain_bounds(vector <string> &lines){
    int dx = terrain.back()->get_width(), dy = terrain.back()->get_height();
    for(int i = 0 ; i < (int)lines.size() ; i ++){
        for(int j = 0 ; j < (int)lines[i].size() ; j ++){
            char c = lines[i][j];
            if(c == '.'){
                if(i == 0 or !(lines[i-1].size() > j and lines[i-1][j] == '.'))  
                    add_terrain_bound(lines, i, j, dx, dy);
            }
        }
    }
}

void Level::init(int level){
    read_map(MAPS_PATH + to_string(level));
    find_sprite_bounds(terrain);
    player = new Player();
    player->set_position(teleporter->get_position().x, teleporter->get_position().y);
}

void Level::add_terrain(vector <string> &lines){
    for(int i = 0 ; i < (int)lines.size() ; i ++){
        for(int j = 0 ; j < (int)lines[i].size() ; j ++){
            char c = lines[i][j];
            if(c == '.'){
                terrain.push_back(new Entity(&block_texture, Vector2f(BLOCK_SCALE.x, BLOCK_SCALE.y)));
                terrain.back()->set_position(j*terrain.back()->get_width(), i * terrain.back()->get_height());
            }
        }
    }
}

void Level::add_stuff(vector <string> &lines, int width, int height){
    for(int i = 0 ; i < (int)lines.size() ; i ++){
        for(int j = 0 ; j < (int)lines[i].size() ; j ++){
            char c = lines[i][j];
            if(c == '$'){
                teleporter = new Waypoint;
                teleporter->set_position(j*width, i*height);
            }
            if(c == '^'){
                rewards.push_back(new Coin);
                rewards.back()->set_position(j*width, (i+0.3)*height);
            }
            if(c == '*'){
                rewards.push_back(new Star);
                rewards.back()->set_position(j*width, (i+0.3)*height);
            }
            if(c == 'M'){
                enemies.push_back(new ArmoredEnemy);
                enemies.back()->set_position(j*width, i*height);
            }   
        }
    }
}

void Level::read_map(string map_path){
    vector <string> lines;
    ifstream file(map_path);
    std::string line;
    while (std::getline(file, line)) { 
        lines.push_back(line);
    }
    add_terrain(lines);
    add_stuff(lines, terrain.back()->get_width(), terrain.back()->get_height());
    find_terrain_bounds(lines);
}

void Level::find_sprite_bounds(const vector<Entity*>& sprites){
    leftmost_point = sprites[0]->get_position().x;
    rightmost_point = leftmost_point + sprites[0]->get_width();
    highest_point = sprites[0]->get_position().y;
    lowest_point = highest_point + sprites[0]->get_height();

    for (auto it = sprites.begin() + 1; it != sprites.end(); ++it) {
        const auto& sprite = *it;
        double spriteLeft = sprite->get_position().x;
        double spriteRight = spriteLeft + sprite->get_width();
        double spriteTop = sprite->get_position().y;
        double spriteBottom = spriteTop + sprite->get_height();

        leftmost_point = min(leftmost_point, spriteLeft);
        rightmost_point = max(rightmost_point, spriteRight);
        highest_point = min(highest_point, spriteTop);
        lowest_point = max(lowest_point, spriteBottom);
    }
}

void Level::adjust_view(){
    double x = player->get_center().x, y = player->get_center().y;
    x = max(x, leftmost_point + WIDTH/2.f);
    x = min(x, rightmost_point - WIDTH/2.f);
    y = min(y, lowest_point - HEIGHT/2.f);
    view.setCenter(x, y);
}

void Level::handle_key_down(Keyboard::Key key){
    switch(key){
        case(Keyboard::Up):
        case(Keyboard::W):
        case(Keyboard::Space):
            player->jump();
            break;
        case(Keyboard::Left):
        case(Keyboard::A):
            if(can_go_left(player->get_sprite()))
                player->go_left();
            break;
        case(Keyboard::Right):
        case(Keyboard::D):
            if(can_go_right(player->get_sprite()))
                player->go_right();
            break;
        default:
            break;
    }
}  

void Level::handle_key_up(Keyboard::Key key){
    switch(key){
        case(Keyboard::Up):
        case(Keyboard::W):
        case(Keyboard::Space):
            player->stop_jump();
            break;
        case(Keyboard::Left):
        case(Keyboard::A):
            player->stop_left();
            break;
        case(Keyboard::Right):
        case(Keyboard::D):
            player->stop_right();
            break;
        default:
            break;
    }
}

void Level::init_heart(){
    heart_sprite = new Sprite;
    heart_sprite->setTexture(heart_texture);
    heart_sprite->setTextureRect(IntRect(level::HEART_X, level::HEART_Y, level::HEART_WIDTH, level::HEART_HEIGHT));
    heart_sprite->setScale(level::HEART_SCALE);
}