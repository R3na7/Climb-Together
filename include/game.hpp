#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <box2d.h>
#include <memory>
#include <string>

#include "player.hpp"
#include "game_menu.hpp"
#include "world.hpp"

class Game {
public:
    Game();
    
    ~Game() = default;
    
    void start();
    bool& isRunning();

    class ResourceManager;

private:

enum class EMENU : std::size_t {
    NONE = 0,
    START,
    PAUSE,
    SETTINGS 
};

private:

    void render();
    void update();

    void updateMenu();

    void initStartMenu(const std::string& background_filepath);

    void initPauseMenu(const std::string& background_filepath);

    void initSettingsMenu(const std::string& background_filepath);

    void restart();

    void playerHandleInput();


    bool _isRunning = true;

    float _window_width;
    float _window_height;

    std::map<EMENU,GameMenu> _menus;

    EMENU _currentMenu; 
    
    World _world;
    
    std::unique_ptr<b2World> _physics_world;

    Player _player;
    Player _second_player;
    Player* _current_player;

    Camera2D _camera;
};

#endif // GAME_HPP
