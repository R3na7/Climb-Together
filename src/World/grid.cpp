#include <iostream>

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Map.hpp>

#include "grid.hpp"
#include <algorithm>
#include <set>

Grid::Grid(const std::vector<int> &grid, const std::vector<Tile> &tiles, const Texture2D &tileset, int width, int height)
: _grid(grid), _tiles(tiles), _tileset(tileset), _width(width), _height(height) {}

Grid::Grid(const std::string &filename) {
    loadFromFile(filename);
}

bool Grid::checkCollision(const Rectangle & hitbox) {

    int x1 = hitbox.x / 256.0f;
    int y1 = hitbox.y / 256.0f;

    int x2 = (hitbox.x + hitbox.width) / 256.0f;
    int y2 = hitbox.y / 256.0f;

    int x3 = (hitbox.x + hitbox.width)  / 256.0f;
    int y3 = (hitbox.y + hitbox.height)  / 256.0f;

    int x4 = hitbox.x  / 256.0f;
    int y4 = (hitbox.y + hitbox.height) / 256.0f;


    _tiles[_grid[ y1 * _width + x1 ]].initHitbox(x1, y1);
    if (CheckCollisionRecs(_tiles[_grid[ y1 * _width + x1 ]].getHitbox(), hitbox)) return true;

    _tiles[_grid[ y2 * _width + x2 ]].initHitbox(x2, y2);
    if (CheckCollisionRecs(_tiles[_grid[ y2 * _width + x2 ]].getHitbox(), hitbox)) return true;

    _tiles[_grid[ y3 * _width + x3 ]].initHitbox(x3, y3);
    if (CheckCollisionRecs(_tiles[_grid[ y3 * _width + x3 ]].getHitbox(), hitbox)) return true;

    _tiles[_grid[ y4 * _width + x4 ]].initHitbox(x4, y4);
    if (CheckCollisionRecs(_tiles[_grid[ y4 * _width + x4 ]].getHitbox(), hitbox)) return true;

    return false;
}

void Grid::render(Layer layer) const {
    const int tileWidth = 256;
    const int tileHeight = 256;

    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {

            int tileIndex = _grid[y * _width + x];

            if (layer == Layer::Up) {

                if (_tiles[tileIndex].getTileClass() == TileClass::WallDown) {
                    Vector2 position = {
                        static_cast<float>(x * tileWidth),
                        static_cast<float>(y * tileHeight)
                    };
        
                    _tiles[tileIndex].render(_tileset, position);
                }
                
            } else {
                if (_tiles[tileIndex].getTileClass() != TileClass::WallDown) {
                    Vector2 position = {
                        static_cast<float>(x * tileWidth),
                        static_cast<float>(y * tileHeight)
                    };
        
                    _tiles[tileIndex].render(_tileset, position);
                }
            }
            

            
        }
    }

}

Texture2D Grid::getTileset() const { return _tileset; }
int Grid::getWidth()  const { return _width; }
int Grid::getHeight() const { return _height; }

void Grid::setTileset(const Texture2D & tileset) {
    _tileset = tileset;
}

void Grid::setWidth(int width) {
    _width = width;
}

void Grid::setHeight(int height) {
    _height = height;
}


Grid::Proxy Grid::operator[](int row)
{
    if (row < 0 || row >= _height) {
        throw std::out_of_range("Row index out of range");
    }
    return Proxy(_grid, row, _width);
}

const Grid::Proxy Grid::operator[](int row) const {
    if (row < 0 || row >= _height) {
        throw std::out_of_range("Row index out of range");
    }
    return Proxy(_grid, row, _width);
}

Grid::Proxy::Proxy(std::vector<int>& grid, int row, int width) : _grid(&grid), _row(row), _width(width) {}

Grid::Proxy::Proxy(const std::vector<int>& grid, int row, int width) : _constGrid(&grid), _row(row), _width(width) {}

int& Grid::Proxy::operator[](int col) {
    return (*_grid)[_row * _width + col];
}

const int& Grid::Proxy::operator[](int col) const {
    return (*_constGrid)[_row * _width + col];
}

bool Grid::loadFromFile(const std::string & filename) {
    tmx::Map map;

    if (!map.load(RES_PATH"worlds/" + filename)) {
        return false;
    }

    const auto& mapSize = map.getTileCount();
    _width = mapSize.x;
    _height = mapSize.y;

    _tiles.clear();
    _grid.clear();
    _grid.resize(_width * _height, 0);

    for (int i = 0; i < 64; ++i) {

        int tilesetX = (i % 8) * 256;
        int tilesetY = (i / 8) * 256;

        Rectangle sourceRec = {
           (float)tilesetX,
           (float)tilesetY,
           (float)256,
           (float)256
        };

        _tiles.push_back(Tile(sourceRec, TileClass::Wall));
        _tiles.back().setId(_tiles.size()-1);
        
    }

    const auto& layers = map.getLayers();
    for (const auto& layer : layers) {
        if (!(layer->getType() == tmx::Layer::Type::Tile)) continue;

        TileClass tileClass;
        
        const auto & tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();

        if (layer->getName() == "Floor")     {
            tileClass = TileClass::Floor;
        }
        if (layer->getName() == "Wall")      {
            tileClass = TileClass::Wall;
        }
        if (layer->getName() == "WallUp")    {
            tileClass = TileClass::WallUp;
        }
        if (layer->getName() == "WallDown")  {
            tileClass = TileClass::WallDown;
        }
        if (layer->getName() == "DoorRight") {
            tileClass = TileClass::DoorRight;
        }
        if (layer->getName() == "DoorLeft")  {
            tileClass = TileClass::DoorLeft;
        }


        for (int y = 0; y < _height; ++y) {

            for (int x = 0; x < _width; ++x) {

                if (tiles[y * _width + x].ID == 0) continue;

                _grid[y * _width + x] = tiles[y * _width + x].ID - 1;
                _tiles[tiles[y * _width + x].ID - 1].setTileClass(tileClass);
            }
        }

    }

    const auto& tileset = map.getTilesets()[0];
    std::string tilesetPath = tileset.getImagePath();

    _tileset = LoadTexture(tilesetPath.c_str());
    return true;
}
