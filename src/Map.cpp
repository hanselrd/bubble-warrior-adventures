#include "Map.hpp"
#include <cppcodec/base64_default_rfc4648.hpp>
#include <pybind11/stl.h>
#include <algorithm>
#include <cstring>
#include <functional>
#include <stdexcept>
#include "Config.hpp"

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
        _texture.loadFromFile(ASSETS_DIR + source.substr(3));
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

const sf::Texture& Map::Tileset::getTexture() const {
    return _texture;
}

Map::Layer::Layer(const Map& map, const pugi::xml_node& layerNode) {
    _name = layerNode.attribute("name").as_string();
    _visible = layerNode.attribute("visible").as_bool(true);

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
                    _tiles.back().setPosition(x, y);
                }

                x += map.getTileWidth();
            }
        }
    }
    else if (type == "objectgroup") {
        _type = Type::Object;

        for (const auto& node : layerNode)
            _objects.push_back(Object(map, node));
    }
    else if (type == "imagelayer")
        _type = Type::Image;
}

const std::string& Map::Layer::getName() const {
    return _name;
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

const std::vector<Map::Object>& Map::Layer::getObjs() const {
    return _objects;
}

void Map::Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto view = target.getView();
    sf::FloatRect viewRect{view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2, view.getSize().x, view.getSize().y};

    if (_type == Type::Tile) {
        for (const auto& tile : _tiles)
            if (viewRect.intersects(tile.getGlobalBounds()))
                target.draw(tile, states);
    }
    else if (_type == Type::Object)
        for (const auto& object : _objects) {
            if (viewRect.intersects(object.getGlobalBounds()))
                target.draw(object, states);
        }
}

Map::Tile::Tile(const Map& map, unsigned gid)
    : _gid(gid) {
    for (const auto& tileset : map.getTilesets()) {
        if (gid > tileset.getFirstGid() &&
            gid < tileset.getFirstGid() + tileset.getTileCount()) {
            const auto& texture = tileset.getTexture();
            setTexture(texture);
            auto tid = gid - tileset.getFirstGid();
            auto columns = (tileset.getColumns() > 0) ? tileset.getColumns() :
                texture.getSize().x / (tileset.getTileWidth() + tileset.getSpacing()) + tileset.getSpacing();
            auto x = tileset.getMargin() + ((tid % columns) * tileset.getTileWidth())
                + (tileset.getSpacing() * (tid % columns));
            auto y = tileset.getMargin() + ((tid / columns) * tileset.getTileHeight())
                + (tileset.getSpacing() * (tid / columns));
            setTextureRect(sf::IntRect(x, y, tileset.getTileWidth(), tileset.getTileHeight()));
            break;
        }
    }
}

unsigned Map::Tile::getGid() const {
    return _gid;
}

Map::Object::Object(const Map& map, const pugi::xml_node& objectNode) {
    _name = objectNode.attribute("name").as_string();
    _type = objectNode.attribute("type").as_string();
    _rect.left = objectNode.attribute("x").as_uint();
    _rect.top = objectNode.attribute("y").as_uint();
    _rect.width = objectNode.attribute("width").as_uint();
    _rect.height = objectNode.attribute("height").as_uint();

    auto gid = objectNode.attribute("gid").as_uint();
    if (gid > 0) {
        // Workaround for Tiled object tile bug
        _rect.top -= _rect.width;
        _tile = std::make_shared<Tile>(std::ref(map), gid);
        setPosition(_rect.left, _rect.top);
    }
}

const std::string& Map::Object::getName() const {
    return _name;
}

const std::string& Map::Object::getType() const {
    return _type;
}

const sf::IntRect& Map::Object::getRect() const {
    return _rect;
}

sf::FloatRect Map::Object::getLocalBounds() const {
    return sf::FloatRect(0.f, 0.f, _rect.width, _rect.height);
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
        .def_property_readonly("objects", &Map::Layer::getObjs);

    py::enum_<Map::Layer::Type>(layer, "Type")
        .value("Tile", Map::Layer::Type::Tile)
        .value("Object", Map::Layer::Type::Object)
        .value("Image", Map::Layer::Type::Image)
        .export_values();

    py::class_<Map::Tile, sf::Transformable>(m_tmx, "Tile")
        .def(py::init<const Map&, unsigned>())
        .def_property_readonly("gid", &Map::Tile::getGid);

    py::class_<Map::Object, Object>(m_tmx, "Object")
        .def(py::init<const Map&, const pugi::xml_node&>())
        .def_property_readonly("name", &Map::Object::getName)
        .def_property_readonly("type", &Map::Object::getType)
        .def_property_readonly("rect", &Map::Object::getRect);
}
