#pragma once
#include "ui_element.hpp"


class Button : public UIElement {

public:

    Button();

    Button(const Vector2& position, const Vector2& size, const std::shared_ptr<Texture2D>& texture);

    Button(const Vector2& position, const std::shared_ptr<Texture2D>& texture);

    ~Button() = default;

    void update();

    void render() const override;

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
        key_t key;
        std::function<void()> action;

    } _action_on_click;

};