#include "world.hpp"

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <iostream>

World::World()
: _player(nullptr) {}

World::World(const Grid & grid, Player * player)
: _grid(std::move(grid)), _player(player) {}

World::World(const std::string &filename, Player* player) 
: World(Grid(filename)) {
    _player = player;    
}

World::World(World&& world)
: 
_grid(std::move(world._grid)), 
_entities(std::move(world._entities)),
_player(world._player),
_is_finished(world._is_finished) 
{
    world._player = nullptr;
}

bool World::initWorld(const std::string &filename) {
    return _grid.loadFromFile(filename);
}

void World::render() const
{

    _grid.render(Layer::Down);

    for (auto & npc : _npcs) {
        npc.render();
    }

    _player->render();

    _grid.render(Layer::Up);
    
    for (auto & interactive_object : _interactiv_objects) {
        interactive_object.render();
    }

    
    //DrawText(TextFormat("X: %f, Y: %f", (_player->getPosition().x / 256.0f), (_player->getPosition().y / 256.0f)), _player->getPosition().x, _player->getPosition().y, 20, WHITE);
}

void World::update() {

    _player->update();

    for (auto & interactive_object : _interactiv_objects) {
        if (interactive_object.isPointInRange(_player->getPosition())) {
            interactive_object.onInteract();
        }
    }

    for (auto & npc : _npcs) {
        if (npc.isPointInRange(_player->getPosition())) {
            npc.onInteract();
        } else {
            npc.setHasPlayedSound(false);
            npc.update();
        }
    }

}

void World::reset() {

}

void World::addEntity(const Entity & entity) {

}

void World::addInteractiveObject(const InteractiveObject &interactive_object) {
    _interactiv_objects.push_back(interactive_object);
}

void World::addNPC(const NPC &nps) {
    _npcs.push_back(nps);
}

void World::removeEntity(const std::string & entity_name) {

}

void World::removeInteractiveObject(const std::string &entity_name) {

}

const Player * World::getPlayer()   const { return _player;   }
Grid World::getGrid()               const { return _grid; }
const std::string &World::getName() const { return _world_name; }
const Sound &World::getBackgroundSound() const { return _background_sound; }

void World::setPlayer(Player* player) {
    _player = player;
}

void World::setFinished(bool finished) {
    _is_finished = finished;
}

void World::setBackgroundSound(const Sound &sound) {
    _background_sound = sound;
}

bool World::isColidable(int x, int y) const {

}
bool World::isFinished() const {
    return _is_finished;
}

World::~World() {
    StopSound(_background_sound);
}