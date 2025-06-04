#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <sstream>

#include "player.hpp"
#include "tile.hpp"
#include "grid.hpp"
#include "npc.hpp"

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
    virtual void start() = 0;
    void reset();
    
    void addEntity(const Entity & entity);
    void addInteractiveObject(const InteractiveObject & interactive_object);
    void addNPC(const NPC & nps);

    void removeEntity(const std::string & entity_name);
    void removeInteractiveObject(const std::string & entity_name);

    const Player * getPlayer() const;
    Grid getGrid() const;
    Texture2D getTileset() const;
    const std::string& getName() const;
    
    void setTileset(const Texture2D & tileset);
    void setPlayer(Player* player);
    void setFinished(bool _finished);
    
    bool isColidable(int x, int y) const;
    bool isFinished() const;
    
    ~World() = default;

protected:
    std::vector<std::unique_ptr<Entity>> _entities;
    std::vector<InteractiveObject> _interactiv_objects;
    std::vector<NPC> _npcs;
    Player* _player;

    Grid _grid;

    bool _is_finished;
    std::string _world_name;
};

class Lobby : public World {
public:
    
    void start();

};

class Dogrld : public World {
public:
    
    void start();

private:
    Texture2D _texture_ending;
};