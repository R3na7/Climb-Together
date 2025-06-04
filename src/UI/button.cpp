#include <UI/button.hpp>

Button::Button() : UIElement(Vector2{0,0},Vector2{0,0},nullptr) {
    _color_state = GRAY;
}

Button::Button(const Vector2& position,const Vector2& size ,const std::shared_ptr<Texture2D>& texture) 
: UIElement(position,size,texture) {

    _color_state = GRAY;
    this->_button_selection = [this]() -> bool {
        return CheckCollisionPointRec(
            GetMousePosition(),
            Rectangle{_position.x,_position.y,_size.x,_size.y}
        );
    };
}

Button::Button(const Vector2& position, const std::shared_ptr<Texture2D>& texture)
: Button(position, Vector2{texture->width,texture->height}, texture) {}

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
            if(IsKeyPressed(_action_on_click.key))
                _action_on_click.action();

        }
        
    }
}

void Button::render() const {
    DrawTexture(*_texture,_position.x,_position.y, _color_state);
    //DrawTextureNPatch();
}

void Button::setSelection(const std::function<bool()>& selection, const std::function<void()>& action_hover) {
    this->_button_selection = selection;
    this->_action_hover = action_hover;
}

void Button::setActionOnClick(key_t button, const std::function<void()>& action) {
    _action_on_click.key = button;
    _action_on_click.action = action;
}



void Button::setPosition(const Vector2& position) {
    _position = position;
}

void Button::setPosition(float x, float y) {
    _position.x = x;
    _position.y = y;
}

Vector2 Button::getPosition() const {
    return Vector2 {_position.x,_position.y};
}

float Button::getWidth() const {
    return _size.x;
}

float Button::getHeight() const {
    return _size.y;
}

const std::function<bool()>& Button::getButtonSelection() const {
    return _button_selection;
}

bool Button::isSelected() const {
    return _isSelected;
};