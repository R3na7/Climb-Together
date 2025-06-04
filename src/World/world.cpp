#include "world.hpp"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <iostream>

bool World::initWorld(const std::string& filename) {

    try
    {
        _is_finished = false;

        tmx::Map map;

        if (!map.load(filename)) {
            return false;
        }

        for (const auto & propertie : map.getProperties()) {
            if (propertie.getName() == "name") _name = propertie.getStringValue(); 
        }

        _width = map.getTileCount().x;
        _height = map.getTileCount().y;

        const auto & tilesets = map.getTilesets();
        if (tilesets.empty()) return false;
        _tileset = LoadTexture(tilesets[0].getImagePath().c_str());

        _tiles.resize(tilesets[0].getTileCount());
        for (auto & tile : tilesets[0].getTiles()) {
            if (tile.ID >= _tiles.size()) continue;

            auto& worldTile = _tiles[tile.ID];
            worldTile._id = tile.ID;
            worldTile._source_rec = {
                static_cast<float>(tile.imagePosition.x),
                static_cast<float>(tile.imagePosition.y),
                static_cast<float>(tilesets[0].getTileSize().x),
                static_cast<float>(tilesets[0].getTileSize().y)
            };

            for (auto& propertie : tile.properties) {
                if (propertie.getName() == "collision") worldTile._is_collision = propertie.getStringValue() == "true" ? true : false;
            }

            for (const auto & obj : tile.objectGroup.getObjects()) {
                if (obj.getShape() == tmx::Object::Shape::Polygon) {
                    for (const auto & point : obj.getPoints()) {
                        worldTile.polygon.push_back({
                            static_cast<float>(point.x),
                            static_cast<float>(point.y)
                        });
                    }
                }
            }

        }

        for (const auto & layer : map.getLayers()) {
            if (layer->getType() == tmx::Layer::Type::Tile) {
                const auto & tile_layer = layer->getLayerAs<tmx::TileLayer>();
                
                Layer world_layer;
                world_layer._name = tile_layer.getName();
                world_layer._is_visible = tile_layer.getVisible();

                for (const auto & propertie : tile_layer.getProperties()) {
                    if (propertie.getName() == "collision") world_layer._is_collision = propertie.getBoolValue();
                }
                
                for (int i = 0; i < tile_layer.getTiles().size(); ++i) {
                    world_layer._grid.push_back(tile_layer.getTiles()[i].ID - 1);
                }

                for (int y = 0; y < _height; ++y) {
                    for (int x = 0; x < _width; ++x) {
                        std::cout << world_layer._grid[y * _width + x] << " ";
                    }
                    std::cout << std::endl;
                }

                _layers.push_back(std::move(world_layer));

            } else if (layer->getType() == tmx::Layer::Type::Object) {
                const auto & objectGroup = layer->getLayerAs<tmx::ObjectGroup>();

                for (const auto & object : objectGroup.getObjects()) {

                    if (object.getType() == "player" && _player) {

                        _player->setPosition({
                            object.getPosition().x,
                            object.getPosition().y
                        });

                    }

                    if (object.getType() == "entity") {

                        // ????????

                    }

                    if (object.getType() == "interactive_object") {

                        InteractiveObject io;

                        io.setPosition({
                            object.getPosition().x,
                            object.getPosition().y
                        });

                        io.scale(object.getAABB().width, object.getAABB().height);

                        // coming soon

                    }
                    
                }

            } 
        }

        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }   

    return true;

}

void World::render() const {

    for (const auto & layer : _layers) {
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                
                int tile_index = layer._grid[y * _width + x];

                const Tile& tile = _tiles[tile_index];
                Rectangle dest_rec = {
                    static_cast<float>(x * tile._source_rec.width),
                    static_cast<float>(y * tile._source_rec.height),
                    tile._source_rec.width,
                    tile._source_rec.height
                };
                
                DrawTexturePro(
                    _tileset,
                    tile._source_rec,
                    dest_rec,
                    {0, 0},
                    0.0f,
                    WHITE
                );

            }
        }
    }

}

void World::update() {}
void World::reset() {}

void World::addEntity(const Entity & entity) {}
void World::addInteractiveObject(const InteractiveObject & interactive_object) {}

void World::removeEntity(int id) {}
void World::removeInteractiveObject(int id) {}

const Player *             World::getPlayer() const {}
const World::Layer &              World::getLayer(const std::string & name) const {}
const Texture2D &          World::getTileset() const {}
const std::string &        World::getName() const {}
const std::vector<Sound> & World::getBackgroundSounds() const {}

void World::setTileset(const Texture2D & tileset) {}
void World::setPlayer(Player* player) {}
void World::setFinished(bool _finished) {}
void World::setBackgroundSound(const Sound & sound) {}

bool World::isColidable(float x, float y) const {}
bool World::isFinished() const {}