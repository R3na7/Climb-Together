#include "object.hpp"

void Object::move(const Vector2& dest) {
    move(dest.x, dest.y); 
}

void Object::move(float x, float y) {
    _position.x += x;
    _position.y += y;
}

void Object::rotate(float degrees) {
    _rotation += degrees;
}

void Object::scale(float height, float width) {
    _scale.y *= height;
    _scale.x *= width;
}

void Object::scale(const Vector2 & scale) {
    _scale.y *= scale.y;
    _scale.x *= scale.x;
}

void Object::setPosition(const Vector2& position) {
    _position = position; 
}

void Object::setPosition(float x, float y) {
    _position = {x, y};
}

void Object::setScale(const Vector2 & scale) {
    _scale = scale;
}

void Object::setScale(float width, float height) {
    _scale = {width, height};
}

void Object::setVelocity(const Vector2 & velocity) {
    _velocity = velocity;
}

void Object::setAcceleration(const Vector2 & acceleration) {
    _acceleration = acceleration;
}

void Object::setRotate(float degrees){
    _rotation = degrees;
}

const Vector2 & Object::getPosition()     const { return _position; }
const Vector2 & Object::getScale()        const { return _scale; }
const Vector2 & Object::getVelocity()     const { return _velocity; }
const Vector2 & Object::getAcceleration() const { return _acceleration; }