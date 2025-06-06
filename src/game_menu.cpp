#include <game_menu.hpp>
#include <constants.hpp>
#include <UI/button.hpp>


GameMenu::GameMenu(const std::shared_ptr<Texture2D>& background_texture) 
: _background(
        Vector2{background_texture->width, background_texture->height},
        Vector2{0,0},
        background_texture
    ),
  _is_active(false) {

}

void GameMenu::addButton(const std::string& name, const Button &button) {
    _buttons.insert({name, button});
}

void GameMenu::setButtonSize(const std::string &name, const Vector2 &size) {
    _buttons.at(name).setSize(size);
}

void GameMenu::setButtonPosition(const std::string &name, const Vector2 &position) {
    _buttons.at(name).setPosition(position);
}


void GameMenu::update() {
    _background.setSize(Vector2{GetScreenWidth(),GetScreenHeight()});
    for(auto& [name,button] : _buttons) {
        button.update();
    }
}

void GameMenu::render() const {
    _background.render();
    for(auto& [name, button] : _buttons) {
        button.render();
    }
}

Button& GameMenu::getButton(const std::string& name) {
    return _buttons.at(name);
}

const Button& GameMenu::getButton(const std::string& name) const {
    return _buttons.at(name);
}

void GameMenu::setActive(bool is_active) {
    _is_active = is_active;
}

bool GameMenu::isActive() const {
    return _is_active;
}
