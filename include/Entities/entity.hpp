#pragma once

#include <raylib.h>
#include <array>
#include <string>
#include "animation_component.hpp"
#include "collidable.hpp"
#include "constants.hpp"

class Entity : public Collidable {
public:

    Entity(const std::array<Texture2D,DIRECTIONS_COUNT>& textures = {}, const Vector2 & position = {0.0f, 0.0f});

    void move(const Vector2& dest);
    void move(float x, float y);

    void updateHitboxes(float x, float y);
    void updateAnimation();

    void scale(float width, float height);

    void addAnimation(const std::string& name);

    void setPosition(const Vector2& position);
    void setPosition(float x, float y);

    Vector2 getPosition() const;

    void update();
    void render() const;


protected:

    void initHitbox();

    std::array<Texture2D, DIRECTIONS_COUNT> _textures;
    RotationStates _rotation_state = RotationStates::Up;

    Vector2 _position;
    Vector2 _scale = {1.0f, 1.0f};

    float _velocity;

    bool _isColliadable;
    int _id;

    AnimationComponent _animation_component;
};