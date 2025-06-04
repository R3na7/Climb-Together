#include "game_menu.hpp"
#include "constants.hpp"
#include <iostream>
#define RGBA_BYTES_COUNT 4


GameMenu::GameMenu() : _is_active(true) {}

bool GameMenu::isActive() {
    return _is_active;
}



StartMenu::StartMenu(bool& isGameRunning) 
:   _isGameRunning(isGameRunning), 
    _start_button(),
    _exit_button() {

}

void StartMenu::drawBackground() {

}

void StartMenu::update() {
        
    _start_button.update();
    _exit_button.update();
}

void StartMenu::render() const {
    

}


StartMenu::~StartMenu() {
    

}



void PauseMenu::update() {

}

void PauseMenu::render() const {
    
}