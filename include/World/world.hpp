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
    
    World();
    
    World(const World & world) = delete;
    World& operator=(const World &) = delete;

    bool initWorld(const std::string & filename);

    void render() const;
    void update();
    void reset();
    
    void addEntity(const Entity & entity);
    void addInteractiveObject(const InteractiveObject & interactive_object);

    void removeEntity(int id);
    void removeInteractiveObject(int id);

    const Player *             getPlayer() const;
    const Layer &              getLayer(const std::string & name) const;
    const Texture2D &          getTileset() const;
    const std::string &        getName() const;
    const std::vector<Sound> & getBackgroundSounds() const;
    
    void setTileset(const Texture2D & tileset);
    void setPlayer(Player* player);
    void setFinished(bool _finished);
    void setBackgroundSound(const Sound & sound);

    bool isColidable(float x, float y) const;
    bool isFinished() const;
    
    ~World() = default;

private:
    std::vector<std::unique_ptr<Entity>> _entities;
    std::vector<InteractiveObject> _interactiv_objects;
    Player* _player;

    std::vector<Layer> _layers;
    std::vector<Tile> _tiles;

    Texture2D _tileset;
    std::vector<Sound> _background_sounds;
    
    std::string _world_name;
    bool _is_finished;

    struct Layer {
        std::vector<int> _grid;
        std::string _name;
        bool _is_visible;
        bool _is_collision;
    };

    struct Tile {
        size_t _id;
        Rectangle _source_rec;
        std::vector<Vector2> polygon;
        bool _is_collision;
    };
};