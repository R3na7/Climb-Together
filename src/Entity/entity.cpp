#include "entity.hpp"
#include <iostream>

Entity::Entity(const std::array<Texture2D,DIRECTIONS_COUNT> & textures)
: _textures(textures), _rotation_state(RotationStates::Up) {}

void Entity::render() const {
    //if (!_is_visible) return;

    // Преобразуем координаты из метров в пиксели
    float screen_x = _position.x * physics_scale;
    float screen_y = _position.y * physics_scale;

    // Получаем текстуру для текущего направления
    Texture2D texture = _textures[0];

    // Параметры исходной текстуры (весь спрайт)
    Rectangle source_rect = {
        0.0f, 
        0.0f,
        (float)texture.width,
        (float)texture.height
    };
    
    // Параметры назначения (на экране)
    Rectangle dest_rect = {
        screen_x,                  // X позиция в пикселях
        screen_y,                  // Y позиция в пикселях
        _scale.x * physics_scale,  // Ширина с учетом масштаба
        _scale.y * physics_scale   // Высота с учетом масштаба
    };
    
    // Точка вращения (центр)
    Vector2 origin = {
        _scale.x * physics_scale * 0.5f,  // Половина ширины
        _scale.y * physics_scale * 0.5f   // Половина высоты
    };
    
    // Рисуем текстуру
    DrawTexturePro(
        texture,
        source_rect,
        dest_rect,
        origin,
        0.0f,       // Угол поворота (можно добавить поле при необходимости)
        WHITE
    );

    // Отладочная информация (опционально)
    // if (0) {
    //     // Красный круг в центре позиции
    //     DrawCircleV({screen_x, screen_y}, 5.0f, RED);
        
    //     // Текст с координатами
    //     std::string coord_text = "x: " + std::to_string(_position.x) + " y: " + std::to_string(_position.y);
    //     DrawText(
    //         coord_text.c_str(), 
    //         screen_x + 20,  // Смещаем текст вправо от объекта
    //         screen_y - 20,  // И немного вверх
    //         20,             // Размер шрифта
    //         RED
    //     );
    // }
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

