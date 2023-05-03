#include "levelselect.hpp"

LevelSelect::LevelSelect(){
    for(int i = 0 ; i < BG_CNT ; i ++){
        if(!bgs[i].loadFromFile(PICS_PATH + "bg/" + to_string(i) + ".png")){
            throw runtime_error("Couldn't open bg");
        }
    }
    bg.setTexture(bgs[0]);
    if(!music.openFromFile(AUDIO_PATH + "levelselect.ogg"))
        throw runtime_error("Couldn't open levelselect music");
    music.setLoop(true);
    exit_button.set_position({0, 0});
    for(int i = 0 ; i < LEVEL_COUNT ; i ++){
        levels[i] = new Button("Level " + to_string(i), "score.ttf", 48);
    }
    int tot_w = levels[0]->get_width() * 3;
    int tot_h = levels[0]->get_height() * ((LEVEL_COUNT + 2)/3);
    int base_y = (HEIGHT/2 - tot_h);
    int base_x = (WIDTH - tot_w)/2;
    int cur_x = base_x, cur_y = base_y;
    for(int i = 0 ; i < LEVEL_COUNT ; i ++){
        if(i % 3 == 0){
            cur_x = base_x;
            cur_y += levels[i]->get_height() + levels[i]->get_margin();
        }
        levels[i]->set_position({cur_x, cur_y});
        cur_x += levels[i]->get_width() + levels[i]->get_margin();
    }
}

void LevelSelect::update(){
    update_cnt ++;
    update_cnt %= (BG_CNT*MENU_SPEED);
    bg.setTexture(bgs[update_cnt/MENU_SPEED]);
    bg.setColor(Color(100, 100, 100));
}

void LevelSelect::render(RenderWindow &window){
    window.setView(window.getDefaultView());
    window.draw(bg);
    exit_button.render(window);
    for(int i = 0 ; i < LEVEL_COUNT ; i ++)
        levels[i]->render(window);
}

bool LevelSelect::check_exit(){
    return exit_button.get_status();
}

void LevelSelect::get_clicked(Vector2f pos){
    exit_button.get_clicked(pos);
    for(int i = 0 ; i < LEVEL_COUNT ; i ++)
        levels[i]->get_clicked(pos);
}

void LevelSelect::get_unclicked(Vector2f pos){
    exit_button.get_unclicked(pos);
    for(int i = 0 ; i < LEVEL_COUNT ; i ++)
        levels[i]->get_unclicked(pos);
}

void LevelSelect::play(){
    if(music.getStatus() != music.Playing)
        music.play();
}

void LevelSelect::stop(){
    if(music.getStatus() == music.Playing)
        music.stop();
}

int LevelSelect::check_level(){
    for(int i = 0 ; i < LEVEL_COUNT ; i ++)
        if(levels[i]->get_status())
            return i;
    return -1;
}