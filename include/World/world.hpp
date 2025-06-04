#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <sstream>

#include "player.hpp"
#include "tile.hpp"
#include "grid.hpp"
#include "interactivable.hpp"

class World {
public:
    
    World();
    World(const Grid & filename, Player * player = nullptr);
    World(const std::string & filename, Player * player = nullptr);
    World(World&& world);
    
    World(const World & world) = delete;
    World& operator=(const World &) = delete;

    bool initWorld(const std::string & filename);

    void render() const;
    void update();
    void start();
    void reset();
    
    void addEntity(const Entity & entity);
    void addInteractiveObject(const InteractiveObject & interactive_object);

    void removeEntity(const std::string & entity_name);
    void removeInteractiveObject(const std::string & entity_name);

    const Player * getPlayer() const;
    Grid getGrid() const;
    Texture2D getTileset() const;
    const std::string& getName() const;
    const Sound & getBackgroundSound() const;
    
    void setTileset(const Texture2D & tileset);
    void setPlayer(Player* player);
    void setFinished(bool _finished);
    void setBackgroundSound(const Sound & sound);

    bool isColidable(int x, int y) const;
    bool isFinished() const;
    
    ~World();

protected:
    std::vector<std::unique_ptr<Entity>> _entities;
    std::vector<InteractiveObject> _interactiv_objects;
    Player* _player;

    Grid _grid;

    bool _is_finished;
    std::string _world_name;
    Sound _background_sound;
};