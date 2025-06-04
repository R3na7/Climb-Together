#include "UI/ui_element.hpp"
#include "ui_element.hpp"

UIElement::UIElement(const Vector2& position, const Vector2& size, const std::shared_ptr<Texture2D>& texture) 
: _position(position), _size(size), _texture(texture) {}

void UIElement::draw(const Vector2 &position, float width_extension, float height_extension) {
        DrawTextureNPatch(
            *_texture,
            _npatch,
            Rectangle{position.x,position.y,width_extension,height_extension},
            Vector2{0.0f,0.0f},
            _rotation,
            _color_state
        );
}
