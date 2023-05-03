#include "mainmenu.hpp"

MainMenu::MainMenu(){
    for(int i = 0 ; i < BG_CNT ; i ++){
        if(!bgs[i].loadFromFile(PICS_PATH + "bg/" + to_string(i) + ".png")){
            throw runtime_error("Couldn't open bg");
        }
    }
    bg.setTexture(bgs[0]);
    int tot_width = start_button.get_width() + BUTTON_MARGIN + exit_button.get_width();
    start_button.set_position({(WIDTH - tot_width)/2.f, HEIGHT/2.f});
    exit_button.set_position({(WIDTH - tot_width)/2.f + BUTTON_MARGIN + start_button.get_width()
                , HEIGHT/2.f});
    if(!music.openFromFile(AUDIO_PATH + "mainmenu.ogg"))
        throw runtime_error("Couldn't open mainmenu music");
    music.setLoop(true);
}

void MainMenu::update(){
    update_cnt ++;
    update_cnt %= (BG_CNT*MENU_SPEED);
    bg.setTexture(bgs[update_cnt/MENU_SPEED]);
}

void MainMenu::render(RenderWindow &window){
    window.setView(window.getDefaultView());
    window.draw(bg);
    start_button.render(window);
    exit_button.render(window);
}

bool MainMenu::check_start(){
    return start_button.get_status();
}

bool MainMenu::check_exit(){
    return exit_button.get_status();
}

void MainMenu::get_clicked(Vector2f pos){
    start_button.get_clicked(pos);
    exit_button.get_clicked(pos);
}

void MainMenu::get_unclicked(Vector2f pos){
    start_button.get_unclicked(pos);
    exit_button.get_unclicked(pos);
}

void MainMenu::play(){
    if(music.getStatus() != music.Playing)
        music.play();
}

void MainMenu::stop(){
    if(music.getStatus() == music.Playing)
        music.stop();
}