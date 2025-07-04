#pragma once
#include <raylib.h>
#include <functional>
#include <memory>


class UIElement {
public:

    using key_t = int;

    UIElement(const std::shared_ptr<Texture2D>& texture);

    UIElement(const Vector2& source_size, const Vector2& texture_coords, const std::shared_ptr<Texture2D>& texture); 

    ~UIElement() = default;

    void render() const;

    void setPosition(const Vector2& position);

    void setPosition(float x, float y);

    void setSize(const Vector2& size);

    const Vector2& getPosition() const;

    const Vector2& getSize() const;

    void setNPatchLayout(NPatchLayout layout); 

public:

    Color color_state = WHITE;

protected:

    NPatchInfo _npatch;

    Vector2 _position;

    float _rotation;

    Vector2 _size;

    std::shared_ptr<Texture2D> _texture;

};
