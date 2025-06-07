#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game() : 
    _window_width(GetScreenWidth()),
    _window_height(GetScreenHeight()),
    _currentMenu(EMENU::START),
    _player({LoadTexture(RES_PATH"player.png")}) 
{
    SetTargetFPS(120);
    
    initStartMenu(RES_PATH"example.jpg");
    
    b2Vec2 gravity(0.0f, 9.8f);
    _physics_world = std::make_unique<b2World>(gravity);
    
    // _player.createPhysicsBody(_physics_world.get(), b2_dynamicBody);
    // _player.scale({2.0f, 2.0f});
    // _world.setPlayer(&_player);    
    _world.initPhysics(_physics_world.get());
    _world.initWorld(RES_PATH"testWorld.tmx");
    

    _camera = { 0 };
    _camera.offset = (Vector2){ _window_width, _window_height };
    _camera.target = {_window_width/2.0f, _window_height/2.0f};
    _camera.rotation = 0.0f;
    _camera.zoom = 2.0f;


    
    
}

void Game::start() {
    _player.scale({5,5});
    while(!WindowShouldClose() && _isRunning) {
        update();
        render();
    }

    CloseWindow();
}

void Game::update() {

    _physics_world->Step(1.0f / 60.0f, 8, 3);
    _world.update();

    _window_width = GetScreenWidth();
    _window_height = GetScreenHeight();
    
    if(0) {
        updateMenu();
    }
    else {
        _physics_world->Step(1.0f / 60.0f, 8, 3);
        _world.update();
        playerHandleInput();

        //_camera.target = { _player.getPosition().x * physics_scale, _player.getPosition().y * physics_scale};
        
<<<<<<< HEAD
        // if (IsKeyDown(KEY_UP)) {
        //     _camera.zoom *= 1.1f;
        // }
        // if (IsKeyDown(KEY_DOWN)) {
        //     _camera.zoom *= 0.9f;
        // }

        // b2Vec2 vel = _player.getPhysicsBody()->GetLinearVelocity();
        // float desiredVel = 0;
        
        // if (IsKeyDown(KEY_RIGHT)) {
        //     desiredVel = 5.0f; // Скорость движения
        // }
        // if (IsKeyDown(KEY_LEFT)) {
        //     desiredVel = -5.0f;
        // }
        // if (GetKeyPressed() == KEY_SPACE) {
        //     _player.getPhysicsBody()->ApplyLinearImpulse({0.0f, -15.0f}, {0.0f, 10.0f}, 1);
        // }
        
        // // Применяем силу для движения
        // float velChange = desiredVel - vel.x;
        // float force = _player.getPhysicsBody()->GetMass() * velChange / (1/60.0f); // F = mv/t
        // _player.getPhysicsBody()->ApplyForce(b2Vec2(force, 0), _player.getPhysicsBody()->GetWorldCenter(), true);
=======

>>>>>>> 9dca9bd (edit)

    }

}

void Game::render() {
    BeginDrawing();
    ClearBackground(BLACK); 
    if(0) {
        _menus.at(_currentMenu).render();
    }
    else {
        BeginMode2D(_camera);  // Начинаем режим 2D с камерой

        EndMode2D();          // Заканчиваем режим 2D
        _world.render(); 
    }

    EndDrawing();
    
}

void Game::playerHandleInput() {
    // Vector2 velocity = _player.getVelocity();

<<<<<<< HEAD
    // Vector2 start_position = _player.getPosition();
    
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
    // if (IsKeyDown(KEY_UP)) {
    //     _camera.zoom += 1.0f;
    // }
    // if (IsKeyDown(KEY_DOWN)) {
    //     _camera.zoom -= 1.0f;
    // }
=======
    Vector2 start_position = _player.getPosition();
    if (IsKeyDown(KEY_UP)) {
        _camera.zoom *= 1.1f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        _camera.zoom *= 0.9f;
    }
>>>>>>> 9dca9bd (edit)

    b2Vec2 vel = _player.getPhysicsBody()->GetLinearVelocity();
    float desiredVel = 0;
    
    if (IsKeyDown(KEY_RIGHT)) {
        desiredVel = 5.0f; // Скорость движения
    }
    if (IsKeyDown(KEY_LEFT)) {
        desiredVel = -5.0f;
    }
    if(GetKeyPressed() == KEY_SPACE) {
        _player.getPhysicsBody()->ApplyLinearImpulse({0,-10},{0,10},1);
    }
    
    // Применяем силу для движения
    float velChange = desiredVel - vel.x;
    float force = _player.getPhysicsBody()->GetMass() * velChange / (1/60.0f); // F = mv/t
    _player.getPhysicsBody()->ApplyForce(b2Vec2(force, 0), _player.getPhysicsBody()->GetWorldCenter(), true);
    
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
    // if (IsKeyDown(KEY_UP)) {
    //     _camera.zoom += 1.0f;
    // }
    // if (IsKeyDown(KEY_DOWN)) {
    //     _camera.zoom -= 1.0f;
    // }

}


void Game::updateMenu() {
    switch (_currentMenu) {
    case EMENU::START: {
        GameMenu& start_menu = _menus.at(_currentMenu);
        start_menu.update();

        Button& play_button = start_menu.getButton("PlayButton");
        play_button.setSize(Vector2{ _window_width / 4, _window_height / 4});
        play_button.setPosition(Vector2{98,100});

        Button& exit_button = start_menu.getButton("ExitButton");
        exit_button.setSize(Vector2{ _window_width / 4, _window_height / 4});
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
