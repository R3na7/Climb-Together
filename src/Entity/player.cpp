#include "player.hpp"
#include <iostream>

Player::Player() 
: Entity(), _name("Shamil") {

    //scale(0.15f, 0.15f);

}

Player::Player(const std::array<Texture2D,DIRECTIONS_COUNT> _textures, const std::string & name) 
: Entity(_textures), _name(name) {}

bool Player::isWASDKeysdown() const {
    if (IsKeyDown(KEY_A))
        return true;
    else if (IsKeyDown(KEY_W))
        return true;
    else if (IsKeyDown(KEY_S))
        return true;
    else if (IsKeyDown(KEY_D))
        return true;
    
    return false;
}

// void Player::render() const {
    
//     const Texture2D& texture = _textures[_rotation_state];

//     Vector2 origin = {
//         (texture.width * _scale.x) / 2,    // Центр по X
//         (texture.height * _scale.y) / 2    // Центр по Y
//     };
    
//     if(isWASDKeysdown()) {
//         switch (_rotation_state) {
//             case RotationStates::Down:
//                 _animation_component.draw(_position);
//                 break;
            
//             case RotationStates::Up:
//                 _animation_component.draw(_position);    
//                 break;

//             case RotationStates::Right:
//                 _animation_component.draw(_position);
//                 break;
            
//             case RotationStates::Left:
//                 _animation_component.draw(_position);
//                 break;
//             default:
//                 break;
//         }
//     }
//     else {
        
//         Rectangle source_rect = {
//             0.0f, 0.0f,                       // Начало текстуры (x, y)
//             (float)texture.width,              // Ширина исходной текстуры
//             (float)texture.height              // Высота исходной текстуры
//         };
        
//         Rectangle dest_rect = {
//             _position.x,                       // Центр по X
//             _position.y,                       // Центр по Y
//             texture.width * _scale.x,          // Ширина с масштабом
//             texture.height * _scale.y          // Высота с масштабом
//         };
        
//         DrawTexturePro(
//             texture,
//             source_rect,
//             dest_rect,
//             origin,
//             0.0f,                              // Угол поворота (если нужно)
//             WHITE                              // Цвет (можно добавить поле)
//         );
//     }


// }

void Player::setName(const std::string & name) {
    _name = name;
}

void Player::setHp(int hp) {
    _hp = hp;
}

const std::string & Player::getName() const { return _name; }
int Player::getHp()                   const { return _hp; }

void Player::interact() {

}