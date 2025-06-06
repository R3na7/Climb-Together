#pragma once

#include <raylib.h>
#include <UI/button.hpp>
#include <map>
#include <string>

#include <iostream>

class GameMenu {
public:

    explicit GameMenu(const std::shared_ptr<Texture2D>& background_texture);
    
    ~GameMenu() = default;

    void update();

    void render() const;
    
    void addButton(const std::string& name, const Button& button);

    void setButtonSize(const std::string& name, const Vector2& size);

    void setButtonPosition(const std::string &name, const Vector2 &position);

    void setActive(bool is_active);

    bool isActive() const;

protected:

    UIElement _background;

    std::map<std::string,Button> _buttons;

    bool _is_active;
};



