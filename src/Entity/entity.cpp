#include "entity.hpp"
#include <iostream>

Entity::Entity(const std::array<Texture2D,DIRECTIONS_COUNT> & textures)
: _textures(textures), _rotation_state(RotationStates::Up) {}

void Entity::render() const {
    
    Texture2D texture = _textures[0];

    //DrawTexture(texture, _position.x * physics_scale, _position.y * physics_scale, WHITE);
    DrawCircleV({_position.x * physics_scale, _position.y * physics_scale}, 10.0f, RED);

    std::cout << "Coordinates on desktop: " << _position.x * physics_scale << " " << _position.y * physics_scale << std::endl;

    Rectangle source_rect = {
        0.0f, 0.0f,                       // Начало текстуры (x, y)
        (float)texture.width,              // Ширина исходной текстуры
        (float)texture.height              // Высота исходной текстуры
    };
    
    Rectangle dest_rect = {
        _position.x * 100,                       // Центр по X
        _position.y * 100,                       // Центр по Y
        100,          // Ширина с масштабом
        100          // Высота с масштабом
    };
    
    Vector2 origin = {
        (_scale.x) / 2,    // Центр по X
        (_scale.y) / 2    // Центр по Y
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


    DrawText(("x: " + std::to_string(_position.x) + " y:" + std::to_string(_position.y)).c_str(), _position.x, _position.y, 100.0f, RED);
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

