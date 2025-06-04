#include "UI/ui_element.hpp"

Button::Button(const Vector2& position, const Texture2D& texture) 
: _box( Rectangle {
        position.x, 
        position.y, 
        static_cast<float>(texture.width), 
        static_cast<float>(texture.height)
    }),
 _texture(texture) {
    this->_button_selection = [this]() -> bool {
        return CheckCollisionPointRec(GetMousePosition(),_box);
    };
 }

Button::Button(
        const std::function<void()>& action, const std::function<void()>& action_hover,
        const Vector2& position, const Texture2D& texture) 
    : Button(position,texture) {

        this->_action_on_click.button = MOUSE_BUTTON_LEFT;
        this->_action_on_click.action = action;
        
        this->_action_hover = action_hover;
}

void Button::update() {
    
    bool wasSelected = _isSelected;

    _isSelected = _button_selection();

    _color_state = GRAY;
    
    if(_isSelected) {
        _color_state = WHITE;

        if(!wasSelected) {
            if(_action_hover)
                _action_hover();
        }

        if(_action_on_click.action) {
            if(IsKeyPressed(_action_on_click.button))
                _action_on_click.action();

        }
        
    }
}

void Button::render() const {
    DrawTexture(_texture,_box.x,_box.y, _color_state);
}

void Button::setSelection(const std::function<bool()>& selection, const std::function<void()>& action_hover) {
    this->_button_selection = selection;
    this->_action_hover = action_hover;
}

void Button::setActionOnClick(key_t button, const std::function<void()>& action) {
    _action_on_click.button = button;
    _action_on_click.action = action;
}



void Button::setPosition(const Vector2& position) {
    _box.x = position.x;
    _box.y = position.y;
}

void Button::setPosition(float x, float y) {
    _box.x = x;
    _box.y = y;
}

Vector2 Button::getPosition() const {
    return Vector2 {_box.x,_box.y};
}

float Button::getWidth() const {
    return _box.width;
}

float Button::getHeight() const {
    return _box.height;
}

const std::function<bool()>& Button::getButtonSelection() const {
    return _button_selection;
}

bool Button::isSelected() const {
    return _isSelected;
};