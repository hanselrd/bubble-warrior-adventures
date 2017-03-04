#include "Tmx.hpp"
#include <cppcodec/base64_default_rfc4648.hpp>
#include <algorithm>
#include <cstring>
#include <functional>
#include <stdexcept>

tmx::Map::Map(const std::string& filename) {
    auto success = _doc.load_file(filename.c_str());

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

        /*Tileset tileset(mapNode.child("tileset"));
        std::cout << "firstgid:" << tileset.getFirstGid() << std::endl;
        std::cout << "name:" << tileset.getName() << std::endl;
        std::cout << "tilewidth:" << tileset.getTileWidth() << std::endl;
        std::cout << "tileheight:" << tileset.getTileHeight() << std::endl;
        std::cout << "spacing:" << tileset.getSpacing() << std::endl;
        std::cout << "margin:" << tileset.getMargin() << std::endl;
        std::cout << "tilecount:" << tileset.getTileCount() << std::endl;
        std::cout << "columns:" << tileset.getColumns() << std::endl;
        std::cout << "Image info: " << std::endl;
        auto texture = tileset.getTexture();
        std::cout << "\t" << texture.getSize().x << " " << texture.getSize().y << std::endl;*/
    }
}

unsigned tmx::Map::getWidth() const {
    return _width;
}

unsigned tmx::Map::getHeight() const {
    return _height;
}

unsigned tmx::Map::getTileWidth() const {
    return _tileWidth;
}

unsigned tmx::Map::getTileHeight() const {
    return _tileHeight;
}

const std::vector<tmx::Tileset>& tmx::Map::getTilesets() const {
    return _tilesets;
}

const std::vector<tmx::Layer>& tmx::Map::getLayers() const {
    return _layers;
}

tmx::Tileset::Tileset(const Map& map, const pugi::xml_node& tilesetNode) {
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
        _texture.loadFromFile("assets/" + source.substr(3));
    }
}

unsigned tmx::Tileset::getFirstGid() const {
    return _firstGid;
}

const std::string& tmx::Tileset::getName() const {
    return _name;
}

unsigned tmx::Tileset::getTileWidth() const {
    return _tileWidth;
}

unsigned tmx::Tileset::getTileHeight() const {
    return _tileHeight;
}

unsigned tmx::Tileset::getSpacing() const {
    return _spacing;
}

unsigned tmx::Tileset::getMargin() const {
    return _margin;
}

unsigned tmx::Tileset::getTileCount() const {
    return _tileCount;
}

unsigned tmx::Tileset::getColumns() const {
    return _columns;
}

const sf::Texture& tmx::Tileset::getTexture() const {
    return _texture;
}

tmx::Layer::Layer(const Map& map, const pugi::xml_node& layerNode) {
    _name = layerNode.attribute("name").as_string();
    _visible = layerNode.attribute("visible").as_bool();

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

const std::string& tmx::Layer::getName() const {
    return _name;
}

tmx::Layer::Type tmx::Layer::getType() const {
    return _type;
}

bool tmx::Layer::isVisible() const {
    return _visible;
}

const std::vector<tmx::Tile>& tmx::Layer::getTiles() const {
    return _tiles;
}

const std::vector<tmx::Object>& tmx::Layer::getObjects() const {
    return _objects;
}

void tmx::Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_type == Type::Tile) {
        auto view = target.getView();
        sf::FloatRect viewRect{view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2, view.getSize().x, view.getSize().y};
        for (const auto& tile : _tiles)
            if (viewRect.intersects(tile.getGlobalBounds()))
                target.draw(tile, states);
    }
    else if (_type == Type::Object)
        for (const auto& object : _objects) {
            auto t = object.getTile();
            if (t != nullptr)
                target.draw(*t, states);
        }
}

tmx::Tile::Tile(const Map& map, unsigned gid)
    : _gid(gid) {
    for (const auto& tileset : map.getTilesets()) {
        if (gid > tileset.getFirstGid() &&
            gid < tileset.getFirstGid() + tileset.getTileCount()) {
            setTexture(tileset.getTexture());
            auto num = gid - tileset.getFirstGid();
            auto texture = tileset.getTexture();
            auto columns = (tileset.getColumns() > 0) ? tileset.getColumns() : texture.getSize().x / tileset.getTileWidth();
            auto x = tileset.getMargin() + ((num % columns) * tileset.getTileWidth())
                + (tileset.getSpacing() * (num % columns));
            auto y = tileset.getMargin() + ((num / columns) * tileset.getTileHeight())
                + (tileset.getSpacing() * (num / columns));
            setTextureRect(sf::IntRect(x, y, tileset.getTileWidth(), tileset.getTileHeight()));
            break;
        }
    }
}

unsigned tmx::Tile::getGid() const {
    return _gid;
}

tmx::Object::Object(const Map& map, const pugi::xml_node& objectNode) {
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
        _tile->setPosition(_rect.left, _rect.top);
    }
}

const std::string& tmx::Object::getName() const {
    return _name;
}

const std::string& tmx::Object::getType() const {
    return _type;
}

const tmx::Tile* tmx::Object::getTile() const {
    return _tile.get();
}

const sf::IntRect& tmx::Object::getRect() const {
    return _rect;
}

void initTmx(py::module& m) {
    using namespace tmx;
    auto m_tmx = m.def_submodule("tmx", "Tmx map parser");

    py::class_<Map>(m_tmx, "Map")
        .def(py::init<const std::string&>())
        .def_property_readonly("width", &Map::getWidth)
        .def_property_readonly("height", &Map::getHeight)
        .def_property_readonly("tilewidth", &Map::getTileWidth)
        .def_property_readonly("tileheight", &Map::getTileHeight)
        .def_property_readonly("layers", &Map::getLayers);

    py::class_<Layer> layer(m_tmx, "Layer");
    layer.def(py::init<const Map&, const pugi::xml_node&>())
        .def_property_readonly("name", &Layer::getName)
        .def_property_readonly("type", &Layer::getType)
        .def_property_readonly("tiles", &Layer::getTiles)
        .def_property_readonly("objects", &Layer::getObjects);

    py::enum_<Layer::Type>(layer, "Type")
        .value("Tile", Layer::Type::Tile)
        .value("Object", Layer::Type::Object)
        .value("Image", Layer::Type::Image)
        .export_values();

    py::class_<Tile, sf::Transformable>(m_tmx, "Tile")
        .def(py::init<const Map&, unsigned>())
        .def_property_readonly("gid", &Tile::getGid);

    py::class_<Object>(m_tmx, "Object")
        .def(py::init<const Map&, const pugi::xml_node&>())
        .def_property_readonly("name", &Object::getName)
        .def_property_readonly("type", &Object::getType)
        .def_property_readonly("tile", &Object::getTile)
        .def_property_readonly("rect", &Object::getRect);
}
