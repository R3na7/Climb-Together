#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game() : 
    window_width(GetScreenWidth()),
    window_height(GetScreenHeight()),
    _currentMenu(EMENU::START) {
    SetTargetFPS(120);
    

    initMenu(EMENU::START,RES_PATH"example.jpg");
    Button play_button (
        Vector2{586,359},
        Vector2{74,129},
        std::make_shared<Texture2D>(LoadTexture(RES_PATH"buttons.png"))
    );
    play_button.setSelection(
        [&play_button]() -> bool {
            auto pos = play_button.getPosition();
            auto size = play_button.getSize();

            return CheckCollisionPointRec(
                GetMousePosition(),
                Rectangle{pos.x,pos.y,size.x,size.y}
            );
        },
        [&play_button](){
            std::cout << "\n\n ---------------------------- \n\n";
            play_button.color_state = WHITE;
        }

    );
    GameMenu& start_menu = _menus.at(EMENU::START);
    start_menu.addButton("PlayButton",play_button);
    start_menu.setActive(true);

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


void Game::initMenu(const EMENU menu_name, const std::string& background_filepath) {
    const auto& background_texture = std::make_shared<Texture2D>(LoadTexture(background_filepath.c_str()));
    _menus.insert({menu_name, GameMenu { background_texture } });
}


void Game::updateMenu() {
    switch (_currentMenu) {
    case EMENU::START: {
        GameMenu& start_menu = _menus.at(_currentMenu);
        start_menu.update();
        start_menu.setButtonSize("PlayButton",Vector2{ window_width / 2, window_height / 4});
        start_menu.setButtonPosition("PlayButton",Vector2{window_width/3,window_height/4});
        break;
    }

    case EMENU::PAUSE:
        break;

    case EMENU::SETTINGS:
        break;
    
    default:
        break;
    }

}