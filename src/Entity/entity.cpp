#include "entity.hpp"
#include <iostream>

Entity::Entity(const std::array<Texture2D,DIRECTIONS_COUNT> & textures, const Vector2 & position)
: _textures(textures), _position(position), _rotation_state(RotationStates::Up) {

}

void Entity::move(const Vector2& dest) {
    move(dest.x, dest.y); 

}

void Entity::move(float x, float y) {
    _position.x += x;
    _position.y += y;

    updateHitboxes(x, y);
    
    if (y > 0.0f) {
        _rotation_state = RotationStates::Down;
        _animation_component.play("WalkingDown");

    } 
    else if (y < 0.0f) {
        _rotation_state = RotationStates::Up;
        _animation_component.play("WalkingUp");

    }
    else if (x < 0.0f) {
        _rotation_state = RotationStates::Left;
        _animation_component.play("WalkingLeft");

    }
    else if (x > 0.0f) {
        _rotation_state = RotationStates::Right;
        _animation_component.play("WalkingRight");
    }
    
}

void Entity::updateHitboxes(float x, float y) {
    _hitbox.x += x;
    _hitbox.y += y;
    
}

void Entity::updateAnimation() {
    _animation_component.update(GetFrameTime());

}

void Entity::addAnimation(const std::string& name) {
    _animation_component.addAnimation(name);
}

void Entity::scale(float width, float height) {
    _scale.x = height;
    _scale.y = width;
}

void Entity::setPosition(const Vector2& position) {
    setPosition(position.x, position.y);
}

void Entity::setPosition(float x, float y) {
    _position.x = x;
    _position.y = y;
    
    initHitbox();

}

Vector2 Entity::getPosition() const {
    return _position;
}



void Entity::render() const {
    
    Texture2D texture = _textures[_rotation_state];
    
    Rectangle source_rect = {
        0.0f, 0.0f,                       // Начало текстуры (x, y)
        (float)texture.width,              // Ширина исходной текстуры
        (float)texture.height              // Высота исходной текстуры
    };
    
    Rectangle dest_rect = {
        _position.x,                       // Центр по X
        _position.y,                       // Центр по Y
        texture.width * _scale.x,          // Ширина с масштабом
        texture.height * _scale.y          // Высота с масштабом
    };
    
    Vector2 origin = {
        (texture.width * _scale.x) / 2,    // Центр по X
        (texture.height * _scale.y) / 2    // Центр по Y
    };
    
    // Рисуем текстуру с центром в _position
    DrawTexturePro(
        texture,
        source_rect,
        dest_rect,
        origin,
        0.0f,                              // Угол поворота (если нужно)
        WHITE                              // Цвет (можно добавить поле)
    );


}

void Entity::initHitbox() {

    _hitbox = {
        _position.x - 55.0f, _position.y - 100.0f, 
        110.0f, 210.0f
    };



}
