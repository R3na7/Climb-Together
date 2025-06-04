#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game()
:   window_width(GetScreenWidth()) 
    , window_height(GetScreenHeight())
    , _menu(std::make_unique<StartMenu>(_isRunning)) {
    SetTargetFPS(120);

    _camera = {0};
    _camera.offset = {static_cast<float>(window_width) / 2, static_cast<float>(window_height) / 2}; 
    _camera.target = {0, 0};
    _camera.rotation = 0.0f;  
    _camera.zoom = 1.0f;      
}

void Game::start() {

    _world.setPlayer(&_player);
    _world.initWorld(RES_PATH"testWorld.tmx");

    while(!WindowShouldClose() && _isRunning) {
        render();
        update();
    }

    CloseWindow();
}


void Game::update() {
    // if(_menu->isActive()) {
    //     _menu->update();
    // }
    // else {

        _world.update();
        
        playerHandleInput();
        updateCamera();

    //}
}

void Game::playerHandleInput() {
    float velocity = _player.getVelocity();

    if (IsKeyDown(KEY_LEFT_SHIFT)) velocity *= 2.0f;

    if (IsKeyDown(KEY_A)) 
    {
        _player.move(-velocity, 0.0f);

    }
    if (IsKeyDown(KEY_D)) 
    {
        _player.move(velocity, 0.0f);

    }
    if (IsKeyDown(KEY_W)) 
    {
        _player.move(0.0f, -velocity);

    }
    if (IsKeyDown(KEY_S)) 
    {
        _player.move(0.0f, velocity);

    }
}

void Game::render() {
    BeginDrawing();
    ClearBackground(BLACK);

    // if(_menu->isActive()) {
    //     _menu->render();
    // }
    // else {
        BeginMode2D(_camera);

            _world.render(); 
        
        EndMode2D();

    //}
    EndDrawing();
    
}

void Game::updateCamera() {

}