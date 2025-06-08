#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game() : 
    _window_width(GetScreenWidth()),
    _window_height(GetScreenHeight()),
    _currentMenu(EMENU::START),
    _player({LoadTexture(RES_PATH"StandingUp.png")}),
    _second_player({LoadTexture(RES_PATH"player.png")}) {
    SetTargetFPS(120);
    
    
    initStartMenu(RES_PATH"example.jpg");
    initPauseMenu(RES_PATH"example.jpg");
    
    b2Vec2 gravity(0.0f, 1.0f);
    _physics_world = std::make_unique<b2World>(gravity);
    _player.createPhysicsBody(_physics_world.get(), b2_dynamicBody);

    _second_player.createPhysicsBody(_physics_world.get(), b2_dynamicBody);

    _world.setPlayer(&_player, &_second_player);    
    _world.initPhysics(_physics_world.get());
    _world.initWorld(RES_PATH"gora.tmx");

    _camera = { 0 };
    _camera.rotation = 0.0f;
    _camera.zoom = 5.0f;


    
    
}

void Game::start() {

    while(!WindowShouldClose() && _isRunning) {
        update();
        render();
    }

    CloseWindow();
}

void Game::update() {

    // _physics_world->Step(1.0f / 60.0f, 8, 3);
    // _world.update();

    _window_width = GetScreenWidth();
    _window_height = GetScreenHeight();

    if(IsKeyPressed(KEY_ESCAPE)) {
        if(_currentMenu == EMENU::PAUSE)
            _currentMenu = EMENU::NONE;
        else
            _currentMenu = EMENU::PAUSE;
    }
    
    if(_currentMenu != EMENU::NONE) {
        updateMenu();
    }
    else {

        if(!_world.isFinished()) {
            _physics_world->Step(1.0f / 60.0f, 8, 3);

            _world.update();

            _camera.target = { _player.getPosition().x * physics_scale, _player.getPosition().y * physics_scale};
            
            playerHandleInput();
        
            _camera.offset = (Vector2){ _window_width/2.0f, _window_height/2.0f };
            
        }
        else {
            _world.reset();
            _currentMenu = _currentMenu = EMENU::START;
        }


    }

    

}

void Game::render() {
    BeginDrawing();
    ClearBackground(BLACK); 
    if(_currentMenu != EMENU::NONE) {
        _menus.at(_currentMenu).render();
    }
    else {
        BeginMode2D(_camera);  // Начинаем режим 2D с камерой

        _world.render(); 
        EndMode2D();          // Заканчиваем режим 2D
    }

    EndDrawing();
    
}

void Game::playerHandleInput() {
    Vector2 velocity = _player.getVelocity();

    Vector2 start_position = _player.getPosition();

    b2Vec2 vel = _player.getPhysicsBody()->GetLinearVelocity();
    float velocity_x = 0;
    float velocity_y = 0;
    
    // if (IsKeyDown(KEY_A)) 
    // {
    //     _player.move(-velocity.x, 0.0f);
    // }
    // if (IsKeyDown(KEY_D)) 
    // {
    //     _player.move(velocity.x, 0.0f);
    // }
    // if (IsKeyDown(KEY_W)) 
    // {
    //     _player.move(0.0f, -velocity.y);
    // }
    // if (IsKeyDown(KEY_S)) 
    // {
    //     _player.move(0.0f, velocity.y);
    // }

    if (IsKeyDown(KEY_UP)) {
        _camera.zoom *= 1.1f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        _camera.zoom *= 0.9f;
    }


    
    if (IsKeyDown(KEY_RIGHT)) {
        velocity_x = 5.0f; // Скорость движения
    }
    if (IsKeyDown(KEY_LEFT)) {
        velocity_x = -5.0f;
    }


    
    // Применяем силу для движения
    float velChange = velocity_x - vel.x;
    float force = _player.getPhysicsBody()->GetMass() * velChange / (1/60.0f); // F = mv/t
    _player.getPhysicsBody()->ApplyForce(b2Vec2(force, 0), _player.getPhysicsBody()->GetWorldCenter(), true);

}


void Game::updateMenu() {
    GameMenu& current_menu = _menus.at(_currentMenu);

    switch (_currentMenu) {
    case EMENU::START: {
        current_menu.update();

        Button& play_button = current_menu.getButton("PlayButton");
        play_button.setSize(Vector2{ _window_width / 4, _window_height / 4});
        play_button.setPosition(Vector2{98,100});

        Button& exit_button = current_menu.getButton("ExitButton");
        exit_button.setSize(Vector2{ _window_width / 4, _window_height / 4});
        exit_button.setPosition(Vector2{100,play_button.getSize().y + 100});
        break;
    }

    case EMENU::PAUSE: {
        current_menu.update();
        break;
    }


    case EMENU::SETTINGS: {
        break;
    }
    
    default:
        break;
    }

}
