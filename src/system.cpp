#include "system.hpp"

System::System(int width, int height){
    window.create(VideoMode(width, height), "Turtix", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    state = IN_GAME; //must start with menu
    for(int i = 0; i < LEVEL_COUNT ; i++){
        levels[i] = new Level;
    }//this can be done outside a for loop
    current_level_id = 2; //level_select must do this.
    levels[current_level_id]->init(current_level_id);
}

System::~System(){
    for(int i = 0; i < LEVEL_COUNT ; i++){
        delete levels[i];
    }
}

void System::run(){
    while (window.isOpen()){
        handle_events();
        update();
        render();
    }
}

void System::handle_key_down(Keyboard::Key key){
    if(key == Keyboard::Key::Escape){
        delete levels[current_level_id];
        window.close();
        is_closed = true;
        exit(0);
    }
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
    while (window.pollEvent(event)){
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
            default:
                break;
        }
    }
}

void System::update(){
    switch(state){
        case(IN_GAME):
            levels[current_level_id]->update();
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

void System::render(){
    window.clear(BLUE);
    switch(state){
        case(IN_GAME):
            levels[current_level_id]->render(window);
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
    window.display();
}