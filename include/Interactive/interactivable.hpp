#pragma once

#include <functional>

#include "raylib.h"
#include "entity.hpp"

class Interactivable {
public:


    Interactivable(float interactive_radius = 100.0f, const std::function<void()> & iteract = [](){});

    void onInteract() const;

    bool hasPlayedSound() const;
    bool isOnInteract() const;
    float getInteractiveRadius() const;
    const std::function<void()> & getInteract() const;

    void setHasPlayedSound(bool hasPlayedSound);
    void setIntaractiveRadius(float interactiveRadius);
    void setInteract(const std::function<void()> & iteract);

protected:
    float _interactive_radius;
    std::function<void()> _interact = [](){};
    bool _isOnInteract;
    bool _hasPlayedSound;
};

class InteractiveObject : public Entity, public Interactivable {
public:

    InteractiveObject(const std::array<Texture2D, DIRECTIONS_COUNT> & textures, float _interactive_radius = 100.0f);

    InteractiveObject(const std::array<Texture2D, DIRECTIONS_COUNT> & textures, float _interactive_radius, const std::function<void()> & interact);

    ~InteractiveObject() = default;

    bool isPointInRange(const Vector2 & point);

};