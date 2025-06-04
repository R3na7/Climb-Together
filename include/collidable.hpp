#pragma once

#include <raylib.h>

class Collidable {
public:

    Rectangle getHitbox() const;

    void setHitbox(const Rectangle & hitbox);
    
protected:
    Rectangle _hitbox;
};