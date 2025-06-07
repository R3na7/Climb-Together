#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <sstream>

#include "player.hpp"
#include "interactivable.hpp"

class World {
    struct Layer;
    struct Tile; 
public:

    World() = default;
    
    World(const World & world) = delete;
    World& operator=(const World &) = delete;

    bool initWorld(const std::string & filename);

    void render() const;
    void update();
    void reset();
    
    void addEntity(const Entity & entity);
    void addInteractiveObject(const InteractiveObject & interactive_object);
    void addBackgroundSound(const Sound & sound);

    void removeEntity(int id);
    void removeInteractiveObject(int id);

    void setPlayer(Player* player);
    void setTileset(const Texture2D & tileset);
    void setFinished(bool _finished);

    const Player *             getPlayer() const;
    const Layer &              getLayer(const std::string & name) const;
    int                        getWidth() const;
    int                        getHeight() const;
    const Texture2D &          getTileset() const;
    const std::string &        getName() const;
    const std::vector<Sound> & getBackgroundSounds() const;

    bool checkCollidable(float x, float y) const;
    bool checkCollidable(const Vector2 & point) const;
    bool checkCollidable(float x, float y, float width, float height) const;
    bool checkCollidable(const Rectangle & point) const;

    bool isFinished() const;
    
    void initPhysics(b2World* world);

private:
    std::vector<std::unique_ptr<Entity>> _entities;
    std::vector<b2Body*> _bodies;

    std::vector<InteractiveObject> _interactiv_objects;
    Player* _player;

    std::vector<Layer> _layers;
    std::vector<Tile> _tiles;

    int _width;
    int _height;

    Texture2D _tileset;
    int _tile_size;
    std::vector<Sound> _background_sounds;
    
    std::string _name;
    bool _is_finished;

    b2World* _physics_world = nullptr;

    struct Layer {
        std::vector<int> _grid;
        std::string _name;
        bool _is_visible;
    };

    struct Tile {
        int _id;
        Rectangle _source_rec;
        // std::vector<Vector2> polygon;
        // bool _is_collision;
        // b2Body* _physics_body = nullptr;
    };
};