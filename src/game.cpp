#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game()
:   _window_width(GetScreenWidth()), _window_height(GetScreenHeight()), 
    _menu(std::make_unique<StartMenu>(_isRunning)),
    _player({LoadTexture(RES_PATH"player.png")})
{
    SetTargetFPS(60);

    b2Vec2 gravity(0.0f, 9.8f);
    _physics_world = std::make_unique<b2World>(gravity);

    _player.createPhysicsBody(_physics_world.get(), b2_dynamicBody);
    _world.setPlayer(&_player);    
    _world.initPhysics(_physics_world.get());
}

void Game::start() {

    while(!WindowShouldClose() && _isRunning) {
        update();
        render();
    }

    CloseWindow();
}

void Game::update() {

    _physics_world->Step(1.0f / 60.0f, 8, 3);
    _world.update();

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

    _world.render(); 

    EndDrawing();
    
}