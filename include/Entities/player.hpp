#pragma once

#include <raylib.h>

#include "entity.hpp"
#include "UI/hud.hpp"

class Player : public Entity {
public:

    Player();

    Player(const std::array<Texture2D,DIRECTIONS_COUNT> _textures, const std::string & name,const Vector2 & position, int hp = 3);
    
    void update();
    void render() const;

    void setName(const std::string & name);
    void setHp(int hp);
    

    const std::string & getName() const;
    int getHp() const;
    float getVelocity();

    void interact();

private:
    int _hp;
    std::string _name;
};