#include "tile.hpp"
#include <iostream>

Tile::Tile(const Rectangle & source_rec, const TileClass & tile_class)
: _source_rec(source_rec), _tile_class(tile_class) {}

void Tile::initHitbox(int x, int y) {

    if (_tile_class == TileClass::Floor) 
    {
        _hitbox = 
        {
            0.0f, 0.0f,
            0.0f, 0.0f
        };
    } 
    else if (_tile_class == TileClass::Wall) 
    {
        _hitbox = 
        {
            x * 256.0f, y * 256.0f,
            256.0f, 256.0f
        };
    }
    else if (_tile_class == TileClass::WallUp) 
    {
        _hitbox = {
            x * 256.0f, y * 256.0f,
            256.0f, 100.0f
        };
    }
    else if (_tile_class == TileClass::WallDown) 
    {
        _hitbox = {
            x * 256.0f, y * 256.0f + 50.0f,
            256.0f, 256.0f
        };
    }
    else if (_tile_class == TileClass::DoorLeft) 
    {
        _hitbox = {
            (x * 256.0f) + 100, y * 256.0f,
            53.0f, 256.0f
        };
    }
    else if (_tile_class == TileClass::DoorRight) 
    {
        _hitbox = {
            x * 256.0f, y * 256.0f + 20.0f,
            256.0f, 10.0f
        };
    }

}

void Tile::render(const Texture2D & tileset, const Vector2 & position) const {

    DrawTextureRec(
        tileset,
        _source_rec, 
        position,
        WHITE
    );  

}

bool Tile::checkCollision(const Vector2 position) const {
    
}

TileClass Tile::getTileClass() const { return _tile_class; }
size_t Tile::getId()           const { return _id;         }

void Tile::setTileClass(const TileClass &tile_class) {
    _tile_class = tile_class;
}

void Tile::setId(size_t id) {
    _id = id;
}
