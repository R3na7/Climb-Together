#pragma once

#include <vector>
#include <exception>

#include "tile.hpp"

enum class Layer {
    Up = 0,
    Down = 1
};

class Grid {
    class Proxy;
public:
    Grid(const std::vector<int> & grid = {}, const std::vector<Tile> & tiles = {}, const Texture2D & tileset = {}, int width = 0, int height = 0);

    Grid(const std::string & filename);

    bool checkCollision(const Rectangle & hitboxes);

    bool loadFromFile(const std::string & filename);

    void render(Layer layer) const;

    Proxy operator[](int row);
    const Proxy operator[](int row) const;
    
    Texture2D getTileset() const; 
    int getWidth() const;
    int getHeight() const;

    void setTileset(const Texture2D & tileset);
    void setWidth(int width);
    void setHeight(int height);

private:
    Texture2D _tileset;
    std::vector<Tile> _tiles; 
    std::vector<int> _grid;
    int _width;
    int _height;

    std::string _filename;
};


class Grid::Proxy {
public:

    Proxy(std::vector<int>& grid, int row, int width);

    Proxy(const std::vector<int>& grid, int row, int width);

    int& operator[](int col);

    const int& operator[](int col) const;
    
private:
    union {
        std::vector<int>* _grid;                
        const std::vector<int>* _constGrid;     
    };
    int _width;
    int _row;
};