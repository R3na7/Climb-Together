#pragma once

#include <raylib.h>

class Collidable {
public:

    Rectangle getHitbox() const;

    void setHitbox(const Rectangle & hitbox);
    void setColliadable(bool colliadable);

    bool isColliadable() const;

protected:
    bool _is_colliadable;
    Rectangle _hitbox;
};