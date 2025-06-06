#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game() : 
    window_width(GetScreenWidth()),
    window_height(GetScreenHeight()),
    _currentMenu(EMENU::START) {
    SetTargetFPS(120);
    

    initStartMenu(RES_PATH"example.jpg");

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
        update();
        render();
    }

    CloseWindow();
}


void Game::update() {
    window_width = GetScreenHeight();
    window_height = GetScreenHeight();

    if(_menus.at(_currentMenu).isActive())
        updateMenu();

}

void Game::render() {
    BeginDrawing();
    ClearBackground(BLACK); 
    if(_menus.at(_currentMenu).isActive()) {
        _menus.at(_currentMenu).render();
    }
    else {
        _world.render(); 
    }

    EndDrawing();
    
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


void Game::initStartMenu(const std::string& background_filepath) {
    const auto& background_texture = std::make_shared<Texture2D>(LoadTexture(background_filepath.c_str()));
    const auto& buttons_textures = std::make_shared<Texture2D>(LoadTexture(RES_PATH"buttons.png"));
    _menus.insert({EMENU::START, GameMenu { background_texture } });

    GameMenu& start_menu = _menus.at(EMENU::START);
    Button&& play_button = Button(Vector2{586,359},Vector2{73,129},buttons_textures);
    Button&& exit_button = Button(Vector2{586,359},Vector2{73,845},buttons_textures);

    play_button.setSelection(
        [this,&start_menu]() -> bool const {
            auto& pos = start_menu.getButton("PlayButton").getPosition();
            auto& size = start_menu.getButton("PlayButton").getSize();
            start_menu.getButton("PlayButton").color_state = GRAY;
            return CheckCollisionPointRec(
                GetMousePosition(),
                Rectangle{pos.x,pos.y,size.x,size.y}
            );
        },
        [this,&start_menu]() {
            start_menu.getButton("PlayButton").color_state = WHITE;
        }
    );

    exit_button.setSelection(
        [this,&start_menu]() -> bool const {
            auto& pos = start_menu.getButton("ExitButton").getPosition();
            auto& size = start_menu.getButton("ExitButton").getSize();
            start_menu.getButton("ExitButton").color_state = GRAY;
            return CheckCollisionPointRec(
                GetMousePosition(),
                Rectangle{pos.x,pos.y,size.x,size.y}
            );
        },
        [this,&start_menu]() {
            start_menu.getButton("ExitButton").color_state = WHITE;
        }
    );

    start_menu.addButton("PlayButton",play_button);
    start_menu.addButton("ExitButton",exit_button);

    start_menu.setActive(true);
}


void Game::updateMenu() {
    switch (_currentMenu) {
    case EMENU::START: {
        GameMenu& start_menu = _menus.at(_currentMenu);
        start_menu.update();

        Button& play_button = start_menu.getButton("PlayButton");
        play_button.setSize(Vector2{ window_width / 2, window_height / 4});
        play_button.setPosition(Vector2{98,100});

        Button& exit_button = start_menu.getButton("ExitButton");
        exit_button.setSize(Vector2{ window_width / 2, window_height / 4});
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