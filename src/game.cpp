#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game() : window_width(GetScreenWidth()), window_height(GetScreenHeight()) {
    SetTargetFPS(120);
    

    initGameMenus();
    Button play {
        Vector2{586,359},
        Vector2{74,129},
        std::make_shared<Texture2D>(LoadTexture(RES_PATH"resources/buttons.png"))
    };
    _menus[MenuType::START_MENU].addButton("PlayButton",play);

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

    _world.update();
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
        _player.move(0, -velocity);

    }
    if (IsKeyDown(KEY_S)) 
    {
        _player.move(0, velocity);

    }
}

void Game::render() {
    BeginDrawing();
    ClearBackground(BLACK);

        _world.render(); 
        
    EndDrawing();
    
}

void Game::updateCamera() {

<<<<<<< HEAD
=======
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
void Game::initGameMenus() {

    _menus.emplace(
        MenuType::START_MENU,
        GameMenu{std::make_shared<Texture2D>(LoadTexture(RES_PATH"resources/example.jpg"))} 
    );

    _menus.emplace(
        MenuType::PAUSE_MENU,
        GameMenu{std::make_shared<Texture2D>(LoadTexture(RES_PATH"resources/example.jpg"))} 
    );

    _menus.emplace(
        MenuType::SETTINGS_MENU,
        GameMenu{std::make_shared<Texture2D>(LoadTexture(RES_PATH"resources/example.jpg"))} 
    );
>>>>>>> d0c1407 (edit)
}