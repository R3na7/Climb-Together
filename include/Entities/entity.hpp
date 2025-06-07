#pragma once

#include <raylib.h>
#include <array>
#include <string>
#include "animation_component.hpp"
#include "collidable.hpp"
#include "object.hpp"
#include "constants.hpp"


class Entity : public Collidable, public Object {
public:

    Entity(const std::array<Texture2D,DIRECTIONS_COUNT>& textures = {});

    void updateHitboxes();
    void updateAnimation();
    void render() const;
    
    void addAnimation(const std::string& name);

    void setVisible(bool visible);

    bool isVisible() const;


protected:

    std::array<Texture2D, DIRECTIONS_COUNT> _textures;
    RotationStates _rotation_state = RotationStates::Up;
    AnimationComponent _animation_component;
    
    bool _is_visible;
};