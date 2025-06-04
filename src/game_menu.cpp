#include "game_menu.hpp"
#include "constants.hpp"
#include <iostream>
#define RGBA_BYTES_COUNT 4

GameMenu::GameMenu() : _is_active(true) {}

bool GameMenu::isActive() {
    return _is_active;
}



StartMenu::StartMenu(bool& isGameRunning) 
:   _isGameRunning(isGameRunning), 
    _start_button(Vector2 {0,0}, LoadTexture(RES_PATH"UI/StartButton.png")),
    _exit_button(Vector2 {0,0}, LoadTexture(RES_PATH"UI/ExitButton.png")) {

    Sound button_hover_sound = LoadSound(RES_PATH"UI/ButtonPressed.mp3");
    
    _start_button.setActionOnClick(
        KEY_ENTER,
        [this]() {
            this->_is_active = false;
            this->playStoryAnim();
        }
    );

    _exit_button.setActionOnClick(
        KEY_ENTER,
        [this]() {
            this->_isGameRunning = false;
        }
    );
    
    auto isMouseOnButtonStart = _start_button.getButtonSelection();
    auto isMouseOnButtonExit = _exit_button.getButtonSelection();

    _start_button.setSelection(
        [this]() -> bool {
            return _selected_button == &_start_button;
        },
        [this,button_hover_sound]() {
            PlaySound(button_hover_sound);
        }
    );

    _exit_button.setSelection(
        [this]() -> bool {
            return _selected_button == &_exit_button;
        },
        [this,button_hover_sound]() {
            PlaySound(button_hover_sound);
        }
    );

    _start_button.setPosition(270.0f,190.0f);

    _exit_button.setPosition(
        _start_button.getPosition().x,
        _start_button.getPosition().y + _start_button.getHeight()
    );

    _background = LoadTexture(RES_PATH"UI/StartMenuBackground.png");

    _arrow.texture = LoadTexture(RES_PATH"UI/Arrow.png");
    _arrow.x_pos = _start_button.getPosition().x - _arrow.texture.width;
    _arrow.y_pos = _start_button.getPosition().y;
    
    

    // //StartMenuBackgroundMusic.mp3
    // _background_music = LoadMusicStream(RES_PATH"UI/StartMenuBackgroundMusic.mp3");
    // _background_music.looping = true;
    
    // PlayMusicStream(_background_music);
}

void StartMenu::update() {
        if(IsKeyPressed(KEY_UP)) {
            _selected_button = &_start_button;
            float dy = _exit_button.getHeight();
            if(_arrow.y_pos - dy >= _start_button.getPosition().y)
                _arrow.y_pos -= dy;
        }
        else if(IsKeyPressed(KEY_DOWN)) {
            _selected_button = &_exit_button;
            float dy = _exit_button.getHeight();
            if(_arrow.y_pos + dy < _exit_button.getPosition().y)
                _arrow.y_pos += dy;
        }

    _start_button.update();
    _exit_button.update();
}

void StartMenu::render() const {
    DrawTexture(_background,0,0,WHITE);
    _start_button.render();
    _exit_button.render();
    DrawTexture(_arrow.texture,_arrow.x_pos,_arrow.y_pos,WHITE);


}

StartMenu::~StartMenu() {
    

    // StopMusicStream(_background_music);
}



void PauseMenu::update() {

}

void PauseMenu::render() const {
    
}

void StartMenu::playStoryAnim() {
    
    double frameTime = GetTime();

    const int frameDelay = 2;

    for(int i = 0; i < _story_textures.size();i++) {
        _story_textures[i] = LoadTexture(
            (std::string(RES_PATH"StoryAnimation/texture") + std::to_string(i) + std::string(".jpg")).c_str()
        );
    }

    for(auto& texture : _story_textures) {
        while(GetTime() - frameTime <= frameDelay) {
            NPatchInfo npatch = {
                .source = Rectangle{0,0, texture.width,texture.height},
                .left  = 0,             // Left border offset
                .top   = 0,           // Top border offset
                .right = 0,           // Right border offset
                .bottom = 0,          // Bottom border offset
                .layout = NPATCH_NINE_PATCH
            };

            BeginDrawing();
            DrawTextureNPatch(
                    texture,
                    npatch,
                    Rectangle{0,0,GetScreenWidth(),GetScreenHeight()},
                    Vector2{0.0f,0.0f},
                    0,
                    WHITE
                );
            EndDrawing();
            if(IsKeyPressed(KEY_ESCAPE)) return;
        }
        frameTime = GetTime();
    }
}