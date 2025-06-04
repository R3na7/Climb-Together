#pragma once
#include <raylib.h>
#include <memory>

#include "player.hpp"
#include "game_menu.hpp"
#include "world.hpp"

class GameMenu;

class Game {
public:
    Game();
    
    ~Game() = default;
    
    void start();
    bool& isRunning();

private:

    void render();
    void update();
    void updateCamera();

    void restart();

    void playerHandleInput();

    void initStartMenu()

    bool _isRunning = true;

    const size_t window_width;
    const size_t window_height;

    std::map<MenuType,GameMenu> _menus;
    GameMenu::Type _currentMenu; 

    
    World _world;
    
    Player _player;

    Camera2D _camera;
};