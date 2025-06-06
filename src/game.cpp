#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game() : 
    _window_width(GetScreenWidth()),
    _window_height(GetScreenHeight()),
    _currentMenu(EMENU::START),
    _player({LoadTexture(RES_PATH"player.png")}) {
    SetTargetFPS(120);
    

    initStartMenu(RES_PATH"example.jpg");

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

    _window_width = GetScreenHeight();
    _window_height = GetScreenHeight();

    if(_menus.at(_currentMenu).isActive())
        updateMenu();

}

void Game::render() {
    BeginDrawing();
    ClearBackground(BLACK); 
    if(_currentMenu != EMENU::NONE) {
        _menus.at(_currentMenu).render();
    }
    else {
        _world.render(); 
    }

    EndDrawing();
    
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


void Game::updateMenu() {
    switch (_currentMenu) {
    case EMENU::NONE:
        break;

    case EMENU::START: {
        GameMenu& start_menu = _menus.at(_currentMenu);
        start_menu.update();

        Button& play_button = start_menu.getButton("PlayButton");
        play_button.setSize(Vector2{ _window_width / 2, _window_height / 4});
        play_button.setPosition(Vector2{98,100});

        Button& exit_button = start_menu.getButton("ExitButton");
        exit_button.setSize(Vector2{ _window_width / 2, _window_height / 4});
        exit_button.setPosition(Vector2{100,play_button.getSize().y + 100});
        break;
    }

    case EMENU::PAUSE: {
        break;
    }


    case EMENU::SETTINGS: {
        break;
    }
    
    default:
        break;
    }

}
