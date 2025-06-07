#pragma once
#include "ui_element.hpp"


class Button : public UIElement {

public:

    explicit Button(const std::shared_ptr<Texture2D>& texture);

    Button(const Vector2& source_size, const Vector2& texture_coords, const std::shared_ptr<Texture2D>& texture);

    ~Button() = default;

    void update();

    void setSelection(const std::function<bool()>& selection, const std::function<void()>& action_hover);

    void setActionOnClick(key_t button, const std::function<void()>& action_on_click);

    bool isSelected() const;

    const std::function<bool()>& getButtonSelection() const;


private:

    bool _isSelected = false;

    std::function<bool()> _button_selection;

    std::function<void()> _action_hover;

    struct {
        key_t key;
        std::function<void()> action;

    } _action_on_click;

};