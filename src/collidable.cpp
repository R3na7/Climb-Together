#include "collidable.hpp"

Rectangle Collidable::getHitbox()     const { return _hitbox; }

void Collidable::setHitbox(const Rectangle & hitbox) {
    _hitbox = hitbox;
}

void Collidable::setColliadable(bool is_colliadable) {
    _is_colliadable = is_colliadable;
}


bool Collidable::isColliadable()              const { return _is_colliadable; }