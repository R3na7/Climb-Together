#include "world.hpp"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <iostream>

bool World::initWorld(const std::string& filename) {
    try {
        _is_finished = false;

        tmx::Map map;

        if (!map.load(filename)) {
            return false;
        }

        loadMapProperties(map);

        const auto & tilesets = map.getTilesets();
        if (tilesets.empty()) return false;

        _tileset = LoadTexture(tilesets[0].getImagePath().c_str());
        _tile_size = tilesets[0].getTileSize().x;

        parsingTile(tilesets);

        for (const auto & layer : map.getLayers()) {
            if (layer->getType() == tmx::Layer::Type::Tile) {
                loadTileLayer(layer);
            } 
            else if (layer->getType() == tmx::Layer::Type::Object) {
                loadObjectLayer(layer);
            } 
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }   

    return true;
}

void World::render() const {
    // Рендерим слои тайлов
    for (const auto& layer : _layers) {
        if (!layer._is_visible) continue;
        
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                int tile_index = layer._grid[y * _width + x];
                if (tile_index == -1) continue;

                const Tile& tile = _tiles[tile_index];
                
                Rectangle dest_rec = {
                    static_cast<float>(x * _tile_size),
                    static_cast<float>(y * _tile_size),
                    static_cast<float>(_tile_size),
                    static_cast<float>(_tile_size)
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

    if (1) {
        for (const auto& body : _bodies) {
            b2Vec2 position = body->GetPosition();
            float angle = body->GetAngle();
            
            for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
                if (f->GetType() == b2Shape::e_polygon) {
                    b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
                    
                    Vector2 vertices[b2_maxPolygonVertices];
                    for (int i = 0; i < poly->m_count; ++i) {
                        b2Vec2 vertex = body->GetWorldPoint(poly->m_vertices[i]);
                        vertices[i] = {
                            vertex.x * physics_scale,
                            vertex.y * physics_scale
                        };
                    }
                    
                    // DrawTriangleStrip(vertices, poly->m_count, Color{255, 0, 0, 128});
                }
            }
        }
    }
}

void World::update() {

    std::cout << "\n\n\n";

    for(int y = 0; y < _height; y++) {
        for(int x = 0; x < _width; x++) {
            std::cout << _layers[0]._grid[y * _width + x] << " ";
        }
        std::cout << "\n";
    }    
 
    // _player->update();
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

void World::setPlayer(Player* player, Player* secondPlayer) {
    _player = player;
    _secondPlayer = _secondPlayer;
}

void World::setTileset(const Texture2D & tileset) {
    _tileset = tileset;
}

void World::setFinished(bool _finished) {
    _is_finished = _finished;
}

Vector2 World::getWorldCenter() const {
    return {
        static_cast<float>(_width * _tile_size) / 2.0f,
        static_cast<float>(_height * _tile_size) / 2.0f
    };
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

std::vector<std::unique_ptr<Entity>> &World::getEntityes() {
    return _entities;
}

bool World::isFinished() const { return _is_finished; }

void World::initPhysics(b2World* world) {
    _physics_world = world;
}

void World::loadMapProperties(const tmx::Map &map) {
    _width = map.getTileCount().x;
    _height = map.getTileCount().y;

    for (const auto & propertie : map.getProperties()) {
        if (propertie.getName() == "name") _name = propertie.getStringValue(); 
    }
}

void World::parsingTile(const std::vector<tmx::Tileset> &tilesets)
{
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
}

void World::loadTileLayer(const tmx::Layer::Ptr &layer) {
    const auto & tile_layer = layer->getLayerAs<tmx::TileLayer>();
                
    Layer world_layer;
    world_layer._name = tile_layer.getName();
    world_layer._is_visible = tile_layer.getVisible();
                
    for (int i = 0; i < tile_layer.getTiles().size(); ++i) {
        world_layer._grid.push_back(tile_layer.getTiles()[i].ID - 1);
    }

    if (world_layer._name == "collision") {
        loadCollisionLayer(world_layer);
    }

    _layers.push_back(world_layer);
}

void World::loadObjectLayer(const tmx::Layer::Ptr &layer) {
    const auto & objectGroup = layer->getLayerAs<tmx::ObjectGroup>();

    for (const auto & object : objectGroup.getObjects()) {
                    
        if (object.getName() == "player" && _player) {

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

        if (object.getName() == "entity") {


        }

        if (object.getType() == "interactive_object") {

        }
                    
    }
}

void World::loadMapProperties(const tmx::Map &map) {
    _width = map.getTileCount().x;
    _height = map.getTileCount().y;

    for (const auto & propertie : map.getProperties()) {
        if (propertie.getName() == "name") _name = propertie.getStringValue(); 
    }
}

void World::parsingTile(const std::vector<tmx::Tileset> &tilesets)
{
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
}

void World::loadTileLayer(const tmx::Layer::Ptr &layer) {
    const auto & tile_layer = layer->getLayerAs<tmx::TileLayer>();
                
    Layer world_layer;
    world_layer._name = tile_layer.getName();
    world_layer._is_visible = tile_layer.getVisible();
                
    for (int i = 0; i < tile_layer.getTiles().size(); ++i) {
        world_layer._grid.push_back(tile_layer.getTiles()[i].ID - 1);
    }

    if (world_layer._name == "collision") {
        loadCollisionLayer(world_layer);
    }

    _layers.push_back(world_layer);
}

void World::loadObjectLayer(const tmx::Layer::Ptr &layer) {
    const auto & objectGroup = layer->getLayerAs<tmx::ObjectGroup>();

    for (const auto & object : objectGroup.getObjects()) {
                    
        if (object.getName() == "player" && _player) {

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

        if (object.getName() == "entity") {


        }

        if (object.getType() == "interactive_object") {

        }
                    
    }
}

void World::loadCollisionLayer(Layer &world_layer) {
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            if (world_layer._grid[y * _width + x] != -1) {
                b2BodyDef box_body_def;
                box_body_def.type = b2_staticBody;
                    
                b2Vec2 body_position {
                    (x * _tile_size + _tile_size / 2.0f) / physics_scale,
                    (y * _tile_size + _tile_size / 2.0f) / physics_scale
                };
                box_body_def.position.Set(body_position.x, body_position.y);
                box_body_def.fixedRotation = true;

                _bodies.push_back(_physics_world->CreateBody(&box_body_def));

                b2PolygonShape shape;
                shape.SetAsBox(
                    (_tile_size / physics_scale) / 2.0f,
                    (_tile_size / physics_scale) / 2.0f
                );

                b2FixtureDef fixture_def;
                fixture_def.shape = &shape;
                fixture_def.density = 1.0f;
                fixture_def.friction = 0.3f;

                _bodies.back()->CreateFixture(&fixture_def);
            }
        }
    }
}

