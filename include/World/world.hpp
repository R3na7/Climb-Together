#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <sstream>

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

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

    bool isFinished() const;
    
    void initPhysics(b2World* world);

private:

    void loadMapProperties(const tmx::Map & map);
    void parsingTile(const std::vector<tmx::Tileset> & tilesets);
    void loadTileLayer(const tmx::Layer::Ptr & layer);
    void loadObjectLayer(const tmx::Layer::Ptr & layer);
    void loadCollisionLayer(Layer & layer);

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
    };
};