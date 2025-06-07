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
        _tile_size = tilesets[0].getTileSize().x;

        _tiles.resize(tilesets[0].getTileCount());
        for (auto & tile : tilesets[0].getTiles()) {

            auto& worldTile = _tiles[tile.ID];
            worldTile._id = tile.ID;
            worldTile._source_rec = {
                static_cast<float>(tile.imagePosition.x),
                static_cast<float>(tile.imagePosition.y),
                static_cast<float>(tilesets[0].getTileSize().x),
                static_cast<float>(tilesets[0].getTileSize().y)
            };

            for (const auto & obj : tile.objectGroup.getObjects()) {
                if (obj.getShape() == tmx::Object::Shape::Polygon) {

                }
            }

        }

        for (const auto & layer : map.getLayers()) {
            if (layer->getType() == tmx::Layer::Type::Tile) {
                const auto & tile_layer = layer->getLayerAs<tmx::TileLayer>();
                
                Layer world_layer;
                world_layer._name = tile_layer.getName();
                world_layer._is_visible = tile_layer.getVisible();
                
                for (int i = 0; i < tile_layer.getTiles().size(); ++i) {
                    world_layer._grid.push_back(tile_layer.getTiles()[i].ID - 1);
                }

                if (world_layer._name == "collision") {
                    
                    for (int y = 0; y < _height; ++y) {
                        for (int x = 0; x < _width; ++x) {
                            if (world_layer._grid[y * _width + x] != -1) {
                                b2BodyDef box_body_def;
                                box_body_def.type = b2_staticBody;
                                
                                b2Vec2 body_position {(x * _tile_size) / physics_scale, (y * _tile_size) / physics_scale};
                                box_body_def.position.Set(body_position.x, body_position.y);
                                box_body_def.fixedRotation = true;

                                std::cout << body_position.x << " " << body_position.y << std::endl; 

                                _bodies.push_back(_physics_world->CreateBody(&box_body_def));

                                b2PolygonShape shape;
                                shape.SetAsBox((_tile_size / physics_scale) / 2.0f, (_tile_size / physics_scale) / 2.0f);

                                b2FixtureDef fixture_def;
                                fixture_def.shape = &shape;
                                fixture_def.density = 1.0f;
                                fixture_def.friction = 0.3;

                                _bodies.back()->CreateFixture(&fixture_def);
                           }
                        }
                    }
                }

                _layers.push_back(world_layer);

            } else if (layer->getType() == tmx::Layer::Type::Object) {
                const auto & objectGroup = layer->getLayerAs<tmx::ObjectGroup>();

                for (const auto & object : objectGroup.getObjects()) {

                    if (object.getName() == "player") {

                        _player->setPosition({
                            object.getPosition().x + object.getAABB().width / 2.0f,
                            object.getPosition().y + object.getAABB().height / 2.0f
                        });

                        _player->setHitbox({
                            object.getAABB().left,
                            object.getAABB().top,
                            object.getAABB().width,
                            object.getAABB().height
                        });

                        _player->setVisible(object.visible());

                        for (const auto & proportie : object.getProperties()) {
                            if (proportie.getName() == "name") _player->setName(proportie.getStringValue());
                            if (proportie.getName() == "hp") _player->setHp(proportie.getIntValue());
                        }

                    }

                    // if (object.getType() == "entity") {

                    //     // ????????

                    // }

                    // if (object.getType() == "interactive_object") {

                    //     InteractiveObject io;

                    //     io.setPosition({
                    //         object.getPosition().x,
                    //         object.getPosition().y
                    //     });

                    //     io.scale(object.getAABB().width, object.getAABB().height);

                    //     // coming soon

                    // }
                    
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
        if (!layer._is_visible) continue;
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                
                int tile_index = layer._grid[y * _width + x];

                if (tile_index == -1) continue;

                const Tile& tile = _tiles[tile_index]; 

                Rectangle dest_rec = {
                    static_cast<float>(x * 100),
                    static_cast<float>(y * 100),
                    100,
                    100
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

    for (auto& entity : _entities) {
        entity->render();
    }

    if (_player) {
        _player->render();
    }

}

void World::update() {
 
    _player->update();

}
void World::reset() {}

void World::addEntity(const Entity & entity) {}
void World::addInteractiveObject(const InteractiveObject & interactive_object) {
    _interactiv_objects.push_back(interactive_object);
}
void World::addBackgroundSound(const Sound & sound) {
    _background_sounds.push_back(sound);
}

void World::removeEntity(int id) {}
void World::removeInteractiveObject(int id) {}

void World::setPlayer(Player* player) {
    _player = player;
}

void World::setTileset(const Texture2D & tileset) {
    _tileset = tileset;
}

void World::setFinished(bool _finished) {
    _is_finished = _finished;
}


const World::Layer & World::getLayer(const std::string & name) const {

    // std::find(_layers.begin(), _layers.end(), [name](const World::Layer & layer){
    //     return layer._name == name;
    // });

}
const Player *             World::getPlayer()           const { return _player;  }
int                        World::getWidth()            const { return _width;   }
int                        World::getHeight()           const { return _height;  }
const Texture2D &          World::getTileset()          const { return _tileset; }
const std::string &        World::getName()             const { return _name;    }
const std::vector<Sound> & World::getBackgroundSounds() const { return _background_sounds; }

bool World::isFinished() const { return _is_finished; }

void World::initPhysics(b2World* world) {
    _physics_world = world;

    
}

