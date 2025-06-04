#pragma once
#include <raylib.h>
#include <functional>

class Button {
private:
    using key_t = int;

public:

    Button(const Vector2& position, const Texture2D& texture);

    Button(
        const std::function<void()>& action_on_click, const std::function<void()>& action_hover,
        const Vector2& position, const Texture2D& texture);

    void update();

    void render() const;

    void setSelection(const std::function<bool()>& selection, const std::function<void()>& action_hover);
    void setActionOnClick(key_t button, const std::function<void()>& action_on_click);
    
    void setPosition(const Vector2& position);
    void setPosition(float x, float y);

    Vector2 getPosition() const;
    float getWidth() const;
    float getHeight() const;

    bool isSelected() const;

    const std::function<bool()>& getButtonSelection() const;


private:

    bool _isSelected = false;

    Color _color_state = GRAY;

    std::function<bool()> _button_selection;
    std::function<void()> _action_hover;

    struct {
        key_t button;
        std::function<void()> action;

    } _action_on_click;

    Rectangle _box;
    Texture2D _texture;
};