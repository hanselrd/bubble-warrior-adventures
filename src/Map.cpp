#include "Enemy.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include <cppcodec/base64_default_rfc4648.hpp>
#include <pybind11/stl.h>
#include <algorithm>
#include <cstring>
#include <functional>
#include <stdexcept>
#include "Config.hpp"

constexpr unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
constexpr unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
constexpr unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

Map::Map(const std::string& filename) {
    auto success = _doc.load_file((MAPS_DIR + filename).c_str());

    if (success) {
        auto mapNode = _doc.child("map");
        if (mapNode.empty())
            throw std::runtime_error("Map node is missing");

        _width = mapNode.attribute("width").as_uint();
        _height = mapNode.attribute("height").as_uint();
        _tileWidth = mapNode.attribute("tilewidth").as_uint();
        _tileHeight = mapNode.attribute("tileheight").as_uint();
        //_health = mapNode.find_attribute("health").as_int();

        for (const auto& node : mapNode) {
            std::string name = node.name();
            if (name == "tileset")
                _tilesets.push_back(Tileset(*this, node));

            if (name == "layer" ||
                name == "objectgroup" ||
                name == "imagelayer")
                _layers.push_back(Layer(*this, node));
        }
    }
}

unsigned Map::getWidth() const {
    return _width;
}

unsigned Map::getHeight() const {
    return _height;
}

unsigned Map::getTileWidth() const {
    return _tileWidth;
}

unsigned Map::getTileHeight() const {
    return _tileHeight;
}

sf::Vector2u Map::getSize() const {
    return sf::Vector2u(getWidth() * getTileWidth(), getHeight() * getTileHeight());
}

const std::vector<Map::Tileset>& Map::getTilesets() const {
    return _tilesets;
}

const std::vector<Map::Layer>& Map::getLayers() const {
    return _layers;
}

Map::Tileset::Tileset(const Map& map, const pugi::xml_node& tilesetNode) {
    _firstGid = tilesetNode.attribute("firstgid").as_uint();
    _name = tilesetNode.attribute("name").as_string();
    _tileWidth = tilesetNode.attribute("tilewidth").as_uint();
    _tileHeight = tilesetNode.attribute("tileheight").as_uint();
    _spacing = tilesetNode.attribute("spacing").as_uint();
    _margin = tilesetNode.attribute("margin").as_uint();
    _tileCount = tilesetNode.attribute("tilecount").as_uint();
    _columns = tilesetNode.attribute("columns").as_uint();

    auto imageNode = tilesetNode.child("image");
    if (!imageNode.empty()) {
        std::string source = imageNode.attribute("source").as_string();
        _texture = std::make_shared<sf::Texture>();
        _texture->loadFromFile(ASSETS_DIR + source.substr(3));
    }
}

unsigned Map::Tileset::getFirstGid() const {
    return _firstGid;
}

const std::string& Map::Tileset::getName() const {
    return _name;
}

unsigned Map::Tileset::getTileWidth() const {
    return _tileWidth;
}

unsigned Map::Tileset::getTileHeight() const {
    return _tileHeight;
}

unsigned Map::Tileset::getSpacing() const {
    return _spacing;
}

unsigned Map::Tileset::getMargin() const {
    return _margin;
}

unsigned Map::Tileset::getTileCount() const {
    return _tileCount;
}

unsigned Map::Tileset::getColumns() const {
    return _columns;
}

std::shared_ptr<sf::Texture> Map::Tileset::getTexture() const {
    return _texture;
}

Map::Layer::Layer(const Map& map, const pugi::xml_node& layerNode) {
    _layerName = layerNode.attribute("name").as_string();
    _visible = layerNode.attribute("visible").as_bool(true);
    //std::string _tempType = layerNode.attribute("type").as_string();

    std::string type = layerNode.name();
    if (type == "layer") {
        _type = Type::Tile;

        auto dataNode = layerNode.child("data");
        std::string encoding = dataNode.attribute("encoding").as_string();

        if (encoding == "base64" &&
            dataNode.attribute("compression").empty()) {
            std::string data = dataNode.child_value();
            data.erase(std::remove_if(std::begin(data), std::end(data),
                std::bind(std::isspace<char>,
                    std::placeholders::_1,
                    std::locale::classic())), std::end(data));
            std::vector<std::uint8_t> decoded = base64::decode(data);
            std::vector<std::uint32_t> gids(decoded.size() / 4);
            std::memcpy(gids.data(), decoded.data(), decoded.size());

            unsigned x = 0, y = 0;
            for (const auto& gid : gids) {
                if (x > 0 && (x / map.getTileWidth()) % map.getWidth() == 0) {
                    x = 0;
                    y += map.getTileHeight();
                }

                if (gid > 0) {
                    _tiles.push_back(Tile(map, gid));
                    _tiles.back().setPosition((float)x, (float)y);
                    _tiles.back().update();
                }

                x += map.getTileWidth();
            }
        }
    }
    else if (type == "objectgroup") {
        for (const auto& node : layerNode) {
            if (_layerName == "NPCs") {
                _type = Type::NPC;
            }            
            if (_layerName == "Item") {
                _type = Type::Item;
            }
            if (_layerName == "Enemy") {
                _type = Type::Enemy;
            }
            if (_layerName == "Spawn") {
                _type = Type::Spawn;
            }
            if (_layerName == "Portal") {
                _type = Type::Portal;
            }
            else {
                _type = Type::Object;
            }
            _objects.push_back(Object(map, node));
        }
    }
    else if (type == "imagelayer")
        _type = Type::Image;
}

const std::string& Map::Layer::getName() const {
    return _layerName;
}

Map::Layer::Type Map::Layer::getType() const {
    return _type;
}

bool Map::Layer::isVisible() const {
    return _visible;
}

const std::vector<Map::Tile>& Map::Layer::getTiles() const {
    return _tiles;
}

const std::vector<Map::Object>& Map::Layer::getObjects() const {
    return _objects;
}


void Map::Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto view = target.getView();
    sf::FloatRect viewRect(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2, view.getSize().x, view.getSize().y);

    if (_visible) {
        if (_type == Type::Tile) {
            for (const auto& tile : _tiles)
                if (viewRect.intersects(tile.getBounds()))
                    target.draw(tile, states);
        }
        else if (_type == Type::Object ||
            _type == Type::Enemy ||
            _type == Type::Item ||
            _type == Type::NPC ||
            _type == Type::Portal) {
            for (const auto& object : _objects)
                if (viewRect.intersects(object.getGlobalBounds()))
                    target.draw(object, states);
        }
    }
}

Map::Tile::Tile(const Map& map, unsigned gid)
    : _gid(gid)
    , _vertices(sf::Quads, 4) {
    bool flippedHorizontally = _gid & FLIPPED_HORIZONTALLY_FLAG;
    bool flippedVertically = _gid & FLIPPED_VERTICALLY_FLAG;
    bool flippedDiagonally = _gid & FLIPPED_DIAGONALLY_FLAG;

    _gid &= ~(FLIPPED_HORIZONTALLY_FLAG |
        FLIPPED_VERTICALLY_FLAG |
        FLIPPED_DIAGONALLY_FLAG);

    for (const auto& tileset : map.getTilesets()) {
        if (_gid > tileset.getFirstGid() &&
            _gid < tileset.getFirstGid() + tileset.getTileCount()) {
            const auto& texture = tileset.getTexture();
            _texture = texture;
            auto tid = _gid - tileset.getFirstGid();
            auto columns = (tileset.getColumns() > 0) ? tileset.getColumns() :
                texture->getSize().x / (tileset.getTileWidth() + tileset.getSpacing()) + tileset.getSpacing();
            auto x = tileset.getMargin() + ((tid % columns) * tileset.getTileWidth())
                + (tileset.getSpacing() * (tid % columns));
            auto y = tileset.getMargin() + ((tid / columns) * tileset.getTileHeight())
                + (tileset.getSpacing() * (tid / columns));

            _vertices[0].position = sf::Vector2f(0.0f, 0.0f);
            _vertices[1].position = sf::Vector2f((float)tileset.getTileWidth(), 0.0f);
            _vertices[2].position = sf::Vector2f((float)tileset.getTileWidth(), (float)tileset.getTileHeight());
            _vertices[3].position = sf::Vector2f(0.0f, (float)tileset.getTileHeight());

            _vertices[0].texCoords = sf::Vector2f(x + 0.5f, y + 0.5f);
            _vertices[1].texCoords = sf::Vector2f(x + (float)tileset.getTileWidth() - 0.5f, y + 0.5f);
            _vertices[2].texCoords = sf::Vector2f(x + (float)tileset.getTileWidth() - 0.5f, y + (float)tileset.getTileHeight() - 0.5f);
            _vertices[3].texCoords = sf::Vector2f(x + 0.5f, y + (float)tileset.getTileHeight() - 0.5f);

            // diag first followed by hori and vert flips
            sf::Vector2f tmp;

            if (flippedVertically) {
                tmp = _vertices[0].texCoords;
                _vertices[0].texCoords.y = _vertices[2].texCoords.y;
                _vertices[1].texCoords.y = _vertices[2].texCoords.y;
                _vertices[2].texCoords.y = tmp.y;
                _vertices[3].texCoords.y = _vertices[2].texCoords.y;
            }

            if (flippedHorizontally) {
                tmp = _vertices[0].texCoords;
                _vertices[0].texCoords.x = _vertices[1].texCoords.x;
                _vertices[1].texCoords.x = tmp.x;
                _vertices[2].texCoords.x = _vertices[1].texCoords.x;
                _vertices[3].texCoords.x = _vertices[0].texCoords.x;
            }

            if (flippedDiagonally) {
                tmp = _vertices[1].texCoords;
                _vertices[1].texCoords = _vertices[3].texCoords;
                _vertices[3].texCoords = tmp;
            }
        }
    }
}

unsigned Map::Tile::getGid() const {
    return _gid;
}

sf::FloatRect Map::Tile::getBounds() const {
    return _vertices.getBounds();
}

void Map::Tile::update() {
    for (std::size_t i = 0; i < _vertices.getVertexCount(); ++i)
        _vertices[i].position = getTransform().transformPoint(_vertices[i].position);
}

void Map::Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_vertices, _texture.get());
}

Map::Object::Object(const Map& map, const pugi::xml_node& objectNode) {
    _tempName = objectNode.attribute("name").as_string();
    _name = _tempName;
     std::string _tempType = objectNode.attribute("type").as_string();

     // Reading entitytype from map
    if (_tempType == "Enemy") {
        _entityType = EntityType::Enemy;
        _rect.left = objectNode.attribute("x").as_uint();
        _rect.top = objectNode.attribute("y").as_uint();
        _rect.width = objectNode.attribute("width").as_uint();
        _rect.height = objectNode.attribute("height").as_uint();
    }
    else if (_tempType == "Item") {
        _entityType = EntityType::Item;
        _rect.left = objectNode.attribute("x").as_uint();
        _rect.top = objectNode.attribute("y").as_uint();
        _rect.width = objectNode.attribute("width").as_uint();
        _rect.height = objectNode.attribute("height").as_uint();
    }
    else if (_tempType == "Player") {
        _entityType = EntityType::Player;
        _rect.left = objectNode.attribute("x").as_uint();
        _rect.top = objectNode.attribute("y").as_uint();
        _rect.width = objectNode.attribute("width").as_uint();
        _rect.height = objectNode.attribute("height").as_uint();
    }
    else if (_tempType == "NPC") {
        _entityType = EntityType::NPC;
        _rect.left = objectNode.attribute("x").as_uint();
        _rect.top = objectNode.attribute("y").as_uint();
        _rect.width = objectNode.attribute("width").as_uint();
        _rect.height = objectNode.attribute("height").as_uint();
        
    }
    else if (_tempType == "Spawn") {
        _entityType = EntityType::Spawn;
        _rect.left = objectNode.attribute("x").as_uint();
        _rect.top = objectNode.attribute("y").as_uint();
        _rect.width = objectNode.attribute("width").as_uint();
        _rect.height = objectNode.attribute("height").as_uint() ;

    }
    else if (_tempType == "Portal") {
        _entityType = EntityType::Portal;
        _rect.left = objectNode.attribute("x").as_uint();
        _rect.top = objectNode.attribute("y").as_uint();
        _rect.width = objectNode.attribute("width").as_uint();
        _rect.height = objectNode.attribute("height").as_uint() ;

    }
    else {
        _entityType = EntityType::Object;
        _rect.left = objectNode.attribute("x").as_uint();
        _rect.top = objectNode.attribute("y").as_uint();
        _rect.width = objectNode.attribute("width").as_uint();
        _rect.height = objectNode.attribute("height").as_uint();
    }

    auto gid = objectNode.attribute("gid").as_uint();
    if (gid > 0) {
        // Workaround for Tiled object tile bug
        _rect.top -= _rect.width;
        _tile = std::make_shared<Tile>(std::ref(map), gid);
        _tile->setPosition((float)_rect.left,(float) _rect.top);
        _tile->update();
    }

    setPosition((float)_rect.left,(float)_rect.top);
}

const std::string& Map::Object::getName() const {
    return _name;
}

const Object::EntityType& Map::Object::getType() const {
    //if (_entityType == EntityType::Enemy ||
    //    _entityType == EntityType::NPC ||
    //    _entityType == EntityType::Item ||
    //    _entityType == EntityType::Player) {
    //}
    //else {
    //    _entityType = Object::EntityType::Object;
    //}
    return _entityType;
}

const sf::IntRect& Map::Object::getRect() const {
    return _rect;
}

sf::FloatRect Map::Object::getLocalBounds() const {
    return sf::FloatRect(0.0f, 0.0f, (float)_rect.width, (float)_rect.height);
}

void Map::Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_tile) {
        states.transform *= getTransform();
        target.draw(*_tile, states);
    }
}

void initMap(py::module& m) {
    auto m_tmx = m.def_submodule("tmx", "Tmx map parser");

    py::class_<Object>(m_tmx, "GameObject");

    py::class_<Map>(m_tmx, "Map")
        .def(py::init<const std::string&>())
        .def_property_readonly("width", &Map::getWidth)
        .def_property_readonly("height", &Map::getHeight)
        .def_property_readonly("tilewidth", &Map::getTileWidth)
        .def_property_readonly("tileheight", &Map::getTileHeight)
        .def_property_readonly("layers", &Map::getLayers);

    py::class_<Map::Layer> layer(m_tmx, "Layer");
    layer.def(py::init<const Map&, const pugi::xml_node&>())
        .def_property_readonly("name", &Map::Layer::getName)
        .def_property_readonly("type", &Map::Layer::getType)
        .def_property_readonly("tiles", &Map::Layer::getTiles)
        .def_property_readonly("objects", &Map::Layer::getObjects);

    py::enum_<Map::Layer::Type>(layer, "Type")
        .value("Tile", Map::Layer::Type::Tile)
        .value("Object", Map::Layer::Type::Object)
        .value("Image", Map::Layer::Type::Image)
        .export_values();

    py::class_<Map::Tile>(m_tmx, "Tile")
        .def(py::init<const Map&, unsigned>())
        .def_property_readonly("gid", &Map::Tile::getGid);

    py::class_<Map::Object, Object>(m_tmx, "Object")
        .def(py::init<const Map&, const pugi::xml_node&>())
        .def_property_readonly("name", &Map::Object::getName)
        .def_property_readonly("type", &Map::Object::getType)
        .def_property_readonly("rect", &Map::Object::getRect);
}
