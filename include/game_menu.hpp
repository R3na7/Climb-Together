#pragma once

#include <raylib.h>
#include <UI/button.hpp>
#include <map>

enum class MenuType {
    START_MENU = 0,
    SETTINGS_MENU,
    PAUSE_MENU
};

class GameMenu {
public:

    explicit GameMenu(const std::shared_ptr<Texture2D>& background_texture);
    
    ~GameMenu() = default;

    void update();
    void render() const;

    void addButton(const std::string& name, const Button& button);

    bool isActive() const;

protected:

    UIElement _background;

    std::map<std::string,Button> _buttons;

    bool _is_active;
};



