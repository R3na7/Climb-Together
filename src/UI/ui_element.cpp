#include "UI/ui_element.hpp"
#include "ui_element.hpp"



UIElement::UIElement(const Vector2& source_size, const Vector2& texture_coords,const std::shared_ptr<Texture2D>& texture) 
:   _position(Vector2{0,0}),
    _size(source_size),
    _npatch(NPatchInfo{Rectangle{texture_coords.x,texture_coords.y,source_size.x,source_size.y},0,0,0,0,NPATCH_NINE_PATCH}), 
    _texture(texture),
    _rotation(0.0f)  {

}

UIElement::UIElement(const std::shared_ptr<Texture2D>& texture) 
: UIElement(
    Vector2{texture->width,texture->height},
    Vector2{0,0},
    texture) {

}



void UIElement::setNPatchLayout(NPatchLayout layout) {
    _npatch.layout = layout;   
}

void UIElement::render() const{
    DrawTextureNPatch(
        *_texture,
        _npatch,
        Rectangle{_position.x, _position.y, _size.x, _size.y},
        Vector2{0.0f, 0.0f},
        _rotation,
        color_state
    );
}


void UIElement::setPosition(const Vector2& position) {
    _position = position;
}

void UIElement::setPosition(float x, float y) {
    _position.x = x;
    _position.y = y;
}

void UIElement::setSize(const Vector2 &size) {
    _size = size;
}

const Vector2& UIElement::getPosition() const {
    return _position;
}


const Vector2& UIElement::getSize() const {
    return _size;
}