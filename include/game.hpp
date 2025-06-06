#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <memory>

#include "player.hpp"
#include "game_menu.hpp"
#include "world.hpp"
#include <string>

class Game {
public:
    Game();
    
    ~Game() = default;
    
    void start();
    bool& isRunning();

    class ResourceManager;

private:

enum class EMENU : std::size_t {
    START = 0,
    PAUSE,
    SETTINGS 
};

private:

    void render();
    void update();

    void updateMenu();

    void restart();

    void playerHandleInput();

    void initStartMenu(const std::string& background_filepath);
    void initPauseMenu(const std::string& background_filepath);
    void initSettingsMenu(const std::string& background_filepath);

    bool _isRunning = true;

    float window_width;
    float window_height;

    std::map<EMENU,GameMenu> _menus;

    EMENU _currentMenu; 
    
    World _world;
    
    Player _player;

    Camera2D _camera;
};

#endif // GAME_HPP