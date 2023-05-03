#include "system.hpp"

System::System(int width, int height){
    window.create(VideoMode(width, height), "Turtix", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    state = IN_GAME; //must start with menu
    for(int i = 0; i < LEVEL_COUNT ; i++){
        levels[i] = new Level;
    }
    current_level_id = 0; //level_select must do this. //map 1 breaks the game 
    levels[current_level_id]->init(current_level_id);
    victory_tab = new SimpleScreen("Winner Winner Chicken dinner!", "victory.ogg", "score.ttf");
    game_over_tab = new SimpleScreen("Game over! :'(", "gameover.ogg", "score.ttf");
    credits_tab = new SimpleScreen("Credits:\n\n\nSoroush Sahraei\n\nParsa Daghigh", "victory.ogg", "score.ttf");
}

System::~System(){
    for(int i = 0; i < LEVEL_COUNT ; i++){
        delete levels[i];
    }
}

void System::run(){
    while (window.isOpen()){
        handle_events();
        if(window.isOpen())update();
        if(window.isOpen())render();
    }
    for(int i = 0; i < LEVEL_COUNT ; i++){
        delete levels[i];
    }
    exit(0);
}

void System::handle_key_down(Keyboard::Key key){
    switch(state){
        case(IN_GAME):
                levels[current_level_id] -> handle_key_down(key);
            break;
        case(PAUSE_MENU):
            break;
        case(MAIN_MENU):
            break;
        case(LEVEL_SELECT):
            break;
        case(VICTORY_SCREEN):
            break;
        case(GAMEOVER_SCREEN):
            break;
        case(CREDITS):
            break;
    }
}

void System::handle_key_up(Keyboard::Key key){
    switch(state){
        case(IN_GAME):
            levels[current_level_id] -> handle_key_up(key);
            break;
        case(PAUSE_MENU):
            break;
        case(MAIN_MENU):
            break;
        case(LEVEL_SELECT):
            break;
        case(VICTORY_SCREEN):
            break;
        case(GAMEOVER_SCREEN):
            break;
        case(CREDITS):
            break;
    }
}

void System::handle_events(){
    Event event;
    while (window.pollEvent(event) and window.isOpen()){
        switch(event.type){
            case(Event::Closed):
                window.close();
                break;
            case(Event::KeyPressed):
                handle_key_down(event.key.code);
                break;
            case(Event::KeyReleased):
                handle_key_up(event.key.code);
                break;
            case(Event::MouseButtonPressed):
                handle_mouse_press(event);
                break;
            case(Event::MouseButtonReleased):
                handle_mouse_release(event);
                break;
            default:
                break;
        }
    }
}

void System::handle_mouse_press(Event ev){
    if(ev.mouseButton.button == Mouse::Right)
        return;
    switch(state){
        case(IN_GAME):
            levels[current_level_id] -> handle_mouse_press({ev.mouseButton.x, ev.mouseButton.y});
            break;
        case(PAUSE_MENU):
            break;
        case(MAIN_MENU):
            break;
        case(LEVEL_SELECT):
            break;
        case(VICTORY_SCREEN):
            break;
        case(GAMEOVER_SCREEN):
            break;
        case(CREDITS):
            break;
    }
}

void System::handle_mouse_release(Event ev){
    if(ev.mouseButton.button == Mouse::Right)
        return;
    switch(state){
        case(IN_GAME):
            levels[current_level_id] -> handle_mouse_release({ev.mouseButton.x, ev.mouseButton.y});
            break;
        case(PAUSE_MENU):
            break;
        case(MAIN_MENU):
            break;
        case(LEVEL_SELECT):
            break;
        case(VICTORY_SCREEN):
            break;
        case(GAMEOVER_SCREEN):
            break;
        case(CREDITS):
            break;
    }
}

void System::update(){
    switch(state){
        case(IN_GAME):
            levels[current_level_id]->update();
            if(levels[current_level_id]->check_lost()){
                delete levels[current_level_id];
                levels[current_level_id] = new Level;
                state = GAMEOVER_SCREEN;
                accumulator = Time::Zero;
                clock.restart();
            }
            if(levels[current_level_id]->check_won()){
                delete levels[current_level_id];
                levels[current_level_id] = new Level;
                state = VICTORY_SCREEN;
                accumulator = Time::Zero;
                clock.restart();
            }
            if(levels[current_level_id]->check_paused()){
                state = PAUSE_MENU;
                levels[current_level_id]->pause(); 
            }
            break;
        case(PAUSE_MENU):
            break;
        case(MAIN_MENU):
            break;
        case(LEVEL_SELECT):
            break;
        case(VICTORY_SCREEN):
            accumulator += clock.restart();
            victory_tab->update();
            if(accumulator > victory_duration){
                victory_tab->stop();
                state = MAIN_MENU;
            }
            break;
        case(GAMEOVER_SCREEN):
            accumulator += clock.restart();
            game_over_tab->update();
            if(accumulator > gameover_duration){
                game_over_tab->stop();
                state = MAIN_MENU;
            }
            break;
        case(CREDITS):
            break;
    }
}

void System::render(){
    window.clear();
    switch(state){
        case(IN_GAME):
            window.clear(BLUE);
            levels[current_level_id]->render(window);
            break;
        case(PAUSE_MENU):
            break;
        case(MAIN_MENU):
            break;
        case(LEVEL_SELECT):
            break;
        case(VICTORY_SCREEN):
            victory_tab->render(window);
            break;
        case(GAMEOVER_SCREEN):
            game_over_tab->render(window);
            break;
        case(CREDITS):
            break;
    }
    window.display();
}