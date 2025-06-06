#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game()
:   window_width(GetScreenWidth()), window_height(GetScreenHeight()), 
    _menu(std::make_unique<StartMenu>(_isRunning)),
    _player({LoadTexture(RES_PATH"player.png")})
{
    SetTargetFPS(120);

    _world.setPlayer(&_player);

    _camera = {0};
    _camera.offset = {static_cast<float>(window_width) / 2, static_cast<float>(window_height) / 2}; 
    _camera.target = _player.getPosition();
    _camera.rotation = 0.0f;  
    _camera.zoom = 1.0f;      
}

void Game::start() {
    
    _world.initWorld(RES_PATH"testWorld.tmx");

    while(!WindowShouldClose() && _isRunning) {
        update();
        render();
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
    Vector2 velocity = _player.getVelocity();

    Vector2 start_position = _player.getPosition();
    
    if (IsKeyDown(KEY_A)) 
    {
        _player.move(-velocity.x, 0.0f);
    }
    if (IsKeyDown(KEY_D)) 
    {
        _player.move(velocity.x, 0.0f);
    }
    if (IsKeyDown(KEY_W)) 
    {
        _player.move(0.0f, -velocity.y);
    }
    if (IsKeyDown(KEY_S)) 
    {
        _player.move(0.0f, velocity.y);
    }
    if (IsKeyDown(KEY_UP)) {
        _camera.zoom += 0.05f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        _camera.zoom -= 0.05f;
    }

    if (_world.checkCollidable(_player.getHitbox())) {
        _player.setPosition(start_position);
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
    _camera.target = _player.getPosition();
}