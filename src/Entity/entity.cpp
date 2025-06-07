#include "entity.hpp"
#include <iostream>

Entity::Entity(const std::array<Texture2D,DIRECTIONS_COUNT> & textures)
: _textures(textures), _rotation_state(RotationStates::Up) {}

void Entity::render() const {
    
    Texture2D texture = _textures[0];

    Rectangle source_rect = {
        0.0f, 0.0f,                       // Начало текстуры (x, y)
        (float)texture.width,              // Ширина исходной текстуры
        (float)texture.height              // Высота исходной текстуры
    };
    
    Rectangle dest_rect = {
        _position.x * 100.0f,                       // Центр по X
        _position.y * 100.0f,                       // Центр по Y
        texture.width * _scale.x * 100.0f,          // Ширина с масштабом
        texture.height * _scale.y * 100.0f          // Высота с масштабом
    };
    
    Vector2 origin = {
        (texture.width * _scale.x * 100.0f) / 2,    // Центр по X
        (texture.height * _scale.y * 100.0f) / 2    // Центр по Y
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


    DrawRectangleLines(_hitbox.x, _hitbox.y, _hitbox.width, _hitbox.height, RED);
    DrawCircleV(_position, 1.0f, RED);

}

void Entity::update() {
    updateHitboxes();

    if (_physics_body) {
        b2Vec2 new_position = _physics_body->GetPosition();
        _position = {new_position.x, new_position.y};
        _rotation = _physics_body->GetAngle() * RAD2DEG;
    }
}

void Entity::updateHitboxes() {
    _hitbox.x = _position.x - _hitbox.width / 2.0f;
    _hitbox.y = _position.y - _hitbox.height / 2.0f;
    
}

void Entity::updateAnimation() {
    _animation_component.update(GetFrameTime());
    
}

void Entity::addAnimation(const std::string& name) {
    _animation_component.addAnimation(name);
}

void Entity::setVisible(bool is_visible) {
    _is_visible = is_visible;
}

bool Entity::isVisible()                  const { return _is_visible; }

