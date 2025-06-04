#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game()
:   window_width(GetScreenWidth()) 
    , window_height(GetScreenHeight())
    , _menu(std::make_unique<StartMenu>(_isRunning)) {
    SetTargetFPS(120);

    _world = std::make_unique<Lobby>();

    _camera = {0};
    _camera.offset = {static_cast<float>(window_width) / 2, static_cast<float>(window_height) / 2}; 
    _camera.target = {0, 0};
    _camera.rotation = 0.0f;  
    _camera.zoom = 1.0f;      
}

void Game::start() {

    _world->setPlayer(&_player);
    _world->start();

    while(!WindowShouldClose() && _isRunning) {
        render();
        update();
    }

    CloseWindow();
}


void Game::update() {
    if(_menu->isActive()) {
        _menu->update();
    }
    else {
        
        if (_world->isFinished()) {
            _world = std::make_unique<Dogrld>();
            _world->setPlayer(&_player);
            _world->start();
        }
        _world->update();
        
        playerHandleInput();
        updateCamera();

    }
}

void Game::playerHandleInput() {
    float velocity = _player.getVelocity();

    if (IsKeyDown(KEY_LEFT_SHIFT)) velocity *= 2.0f;

    if (IsKeyDown(KEY_A)) 
    {
        _player.move(-velocity, 0.0f);

        if (_world->getGrid().checkCollision(_player.getHitbox())) {
            _player.setPosition(_player.getPosition().x + velocity, _player.getPosition().y);
        }
    }
    if (IsKeyDown(KEY_D)) 
    {
        _player.move(velocity, 0.0f);

        if (_world->getGrid().checkCollision(_player.getHitbox())) {
            _player.setPosition(_player.getPosition().x - velocity, _player.getPosition().y);
        }
    }
    if (IsKeyDown(KEY_W)) 
    {
        _player.move(0, -velocity);

        if (_world->getGrid().checkCollision(_player.getHitbox())) {
            _player.setPosition(_player.getPosition().x, _player.getPosition().y + velocity);
        }
    }
    if (IsKeyDown(KEY_S)) 
    {
        _player.move(0, velocity);
        
        if (_world->getGrid().checkCollision(_player.getHitbox())) {
            _player.setPosition(_player.getPosition().x, _player.getPosition().y - velocity);
        }
    }
}

void Game::render() {
    BeginDrawing();
    ClearBackground(BLACK);

    if(_menu->isActive()) {
        _menu->render();
    }
    else {
        BeginMode2D(_camera);

            _world->render(); 
        
        EndMode2D();

    }
    EndDrawing();
    
}

void Game::updateCamera() {
    Vector2 playerPos = _player.getPosition();
    _camera.target.x = Lerp(_camera.target.x, playerPos.x, 0.05f);
    _camera.target.y = Lerp(_camera.target.y, playerPos.y, 0.05f);

    // Получаем размеры карты (предполагая, что у World есть методы getMapWidth() и getMapHeight())
    float mapWidth = _world->getGrid().getWidth() * 256.0f;  // в пикселях
    float mapHeight = _world->getGrid().getHeight() * 256.0f; // в пикселях
    
    // Рассчитываем половину видимой области камеры
    float cameraHalfWidth = (window_width / 2.0f) / _camera.zoom;
    float cameraHalfHeight = (window_height / 2.0f) / _camera.zoom;
    
    // Ограничиваем камеру в пределах карты
    _camera.target.x = Clamp(_camera.target.x, cameraHalfWidth, mapWidth - cameraHalfWidth);
    _camera.target.y = Clamp(_camera.target.y, cameraHalfHeight, mapHeight - cameraHalfHeight);

    if (IsKeyDown(KEY_UP)) {
            _camera.zoom += 0.01f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        if (_camera.zoom > 0.3f) {
            _camera.zoom -= 0.01f;
        }
    }
    
    // Также ограничиваем зум, чтобы не было слишком маленького или большого масштаба
    _camera.zoom = Clamp(_camera.zoom, 0.1f, 3.0f);
}