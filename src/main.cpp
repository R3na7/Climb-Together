#include <iostream>

#include <raylib.h>

#include "game.hpp"

int main(void) {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
    InitWindow(1280, 720, "Climb Together!");
    InitAudioDevice();

    
    Game game;
    
    game.start();

    return 0;
}