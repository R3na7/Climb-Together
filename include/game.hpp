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
    void loadWorld(const std::string& _name);
    void update();
    void updateCamera();
    void pause();

    void playerHandleInput();

    bool _isRunning = true;

    const size_t window_width;
    const size_t window_height;

    std::unique_ptr<GameMenu> _menu;
    
    std::unique_ptr<World> _world;
    
    Player _player;

    Camera2D _camera;
};