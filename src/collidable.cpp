#include "collidable.hpp"

Rectangle Collidable::getHitbox()     const { return _hitbox; }

void Collidable::setHitbox(const Rectangle & hitbox) {
    _hitbox = hitbox;
}
