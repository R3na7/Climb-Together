#pragma once

#include <raylib.h>
#include <memory>

#include "entity.hpp"
#include "collidable.hpp"

enum class TileClass {
    Floor = 0,
    Wall = 1,
    WallUp = 2,
    WallDown = 3,
    DoorRight = 4,
    DoorLeft = 5,
    None = 6
};

class Tile : public Collidable {
public:

    Tile(const Rectangle & source_rec, const TileClass & _tile_class);
 
    void render(const Texture2D & tileset, const Vector2 & dest_rec) const;
    bool checkCollision(const Vector2 position) const;

    void initHitbox(int x, int y);

    TileClass getTileClass() const;
    size_t getId() const;

    void setTileClass(const TileClass & tile_class);
    void setId(size_t id);

private:
    size_t _id;
    TileClass _tile_class;
    Rectangle _source_rec;
};