#pragma once
#include <raylib.h>
#include <box2d.h>
#include <memory>

#include "player.hpp"
#include "game_menu.hpp"
#include "world.hpp"

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

    const size_t _window_width;
    const size_t _window_height;

    std::unique_ptr<GameMenu> _menu;
    
    World _world;
    
    std::unique_ptr<b2World> _physics_world;

    Player _player;

    Camera2D _camera;
};