#pragma once
#include <raylib.h>
#include <functional>
#include <memory>

class UIElement {
public:

    using key_t = int;

    UIElement(const Vector2& position, const Vector2& size, const std::shared_ptr<Texture2D>& texture); 

    ~UIElement() = default;

    virtual void render() const = 0;

protected:

    void draw(const Vector2& position, float width_extension, float height_extension);

    Color _color_state = WHITE;

    NPatchInfo _npatch;

    Vector2 _position;

    float _rotation;

    Vector2 _size;

    std::shared_ptr<Texture2D> _texture;

};
