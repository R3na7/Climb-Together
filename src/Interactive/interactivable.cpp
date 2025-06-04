#include <Interactive/interactivable.hpp>
#include <raymath.h>
#include <iostream>
#include "interactivable.hpp"


Interactivable::Interactivable(float interactive_radius, const std::function<void()> & interact)
: _interactive_radius(interactive_radius), _interact(interact)  {}

void Interactivable::onInteract() const {
    if(_interact) {
        _interact();
    }
}

float Interactivable::getInteractiveRadius()                 const { return _interactive_radius; }

bool Interactivable::hasPlayedSound() const { return _hasPlayedSound; }
bool Interactivable::isOnInteract() const { return _isOnInteract; }
const std::function<void()> & Interactivable::getInteract() const { return _interact; }

void Interactivable::setHasPlayedSound(bool hasPlayedSound) {
    _hasPlayedSound = hasPlayedSound;
}

void Interactivable::setIntaractiveRadius(float interactiveRadius)
{
    _interactive_radius = interactiveRadius;
}

void Interactivable::setInteract(const std::function<void()> & interact) {
    _interact = interact;
}

InteractiveObject::InteractiveObject(const std::array<Texture2D, DIRECTIONS_COUNT> & textures, float _interactive_radius)
: Interactivable(_interactive_radius, nullptr), Entity(textures) {}


InteractiveObject::InteractiveObject(const std::array<Texture2D, DIRECTIONS_COUNT> & textures, float interactive_radius, const std::function<void()> & interact)
: Interactivable(_interactive_radius, interact), Entity(textures) {}

bool InteractiveObject::isPointInRange(const Vector2 & point) {
    
    Vector2 direction = {
        point.x - _position.x,
        point.y - _position.y
    };
    
    float distance_squared = direction.x * direction.x + direction.y * direction.y;
    float radius_squared = _interactive_radius * _interactive_radius;

    _isOnInteract = distance_squared <= radius_squared;
    return _isOnInteract;
}