#include "UI/ui_element.hpp"
#include "ui_element.hpp"

UIElement::UIElement(const Vector2& position, const Vector2& size, const std::shared_ptr<Texture2D>& texture) 
: _position(position), _size(size), _texture(texture) {}

