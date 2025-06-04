#include <UI/button.hpp>


Button::Button(const Vector2& size,const Vector2& texture_coords,const std::shared_ptr<Texture2D>& texture) 
: UIElement(size,texture_coords,texture) {

    _color_state = GRAY;
    this->_button_selection = [this]() -> bool {
        return CheckCollisionPointRec(
            GetMousePosition(),
            Rectangle{_position.x,_position.y,_size.x,_size.y}
        );
    };
}

Button::Button(const std::shared_ptr<Texture2D>& texture) : UIElement(texture) {}

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
    UIElement::render();
}

void Button::setSelection(const std::function<bool()>& selection, const std::function<void()>& action_hover) {
    this->_button_selection = selection;
    this->_action_hover = action_hover;
}

void Button::setActionOnClick(key_t button, const std::function<void()>& action) {
    _action_on_click.key = button;
    _action_on_click.action = action;
}

const std::function<bool()>& Button::getButtonSelection() const {
    return _button_selection;
}

bool Button::isSelected() const {
    return _isSelected;
};