#include <Menu/game_menu.hpp>
#include <constants.hpp>
#include <game_menu.hpp>



GameMenu::GameMenu(const std::shared_ptr<Texture2D>& background_texture) 
: _background(background_texture), _is_active(true) {

}

void GameMenu::addButton(const std::string &name, const Button &button) {
    _buttons.insert({name,button});
}

void GameMenu::update() {
 
    for(std::pair<std::string,Button>& p : _buttons) {
        p.second.update();
    }
}

void GameMenu::render() {
    _background.render();
    for(std::pair<std::string,Button>& p : _buttons) {
        p.second.render();
    }
}


bool GameMenu::isActive() const {
    return _is_active;
}
