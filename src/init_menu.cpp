#include <game.hpp>


void Game::initStartMenu(const std::string& background_filepath) {
    const auto& background_texture = std::make_shared<Texture2D>(LoadTexture(background_filepath.c_str()));
    const auto& buttons_textures = std::make_shared<Texture2D>(LoadTexture(RES_PATH"buttons.png"));
    _menus.insert({EMENU::START, GameMenu { background_texture } });

    GameMenu& start_menu = _menus.at(EMENU::START);
    Button&& play_button = Button(Vector2{586,359},Vector2{73,129},buttons_textures);
    Button&& exit_button = Button(Vector2{586,359},Vector2{73,845},buttons_textures);

    play_button.setSelection(
        [this,&start_menu]() -> bool const {
            auto& pos = start_menu.getButton("PlayButton").getPosition();
            auto& size = start_menu.getButton("PlayButton").getSize();
            start_menu.getButton("PlayButton").color_state = GRAY;
            return CheckCollisionPointRec(
                GetMousePosition(),
                Rectangle{pos.x,pos.y,size.x,size.y}
            );
        },
        [this,&start_menu]() {
            start_menu.getButton("PlayButton").color_state = WHITE;
        }
    );

    play_button.setActionOnClick(
        MOUSE_BUTTON_LEFT,
        [this](){
            _currentMenu = EMENU::NONE; 
        }
    );

    exit_button.setSelection(
        [this,&start_menu]() -> bool const {
            auto& pos = start_menu.getButton("ExitButton").getPosition();
            auto& size = start_menu.getButton("ExitButton").getSize();
            start_menu.getButton("ExitButton").color_state = GRAY;
            return CheckCollisionPointRec(
                GetMousePosition(),
                Rectangle{pos.x,pos.y,size.x,size.y}
            );
        },
        [this,&start_menu]() {
            start_menu.getButton("ExitButton").color_state = WHITE;
        }
    );

    exit_button.setActionOnClick(
        MOUSE_BUTTON_LEFT,
        [this](){
            _isRunning = false;
        }
    );

    start_menu.addButton("PlayButton",play_button);
    start_menu.addButton("ExitButton",exit_button);

    start_menu.setActive(true);
}


void initPauseMenu(const std::string& background_filepath) {

}

void initSettingsMenu(const std::string& background_filepath) {

}
