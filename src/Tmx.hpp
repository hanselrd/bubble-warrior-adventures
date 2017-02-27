#pragma once
#include <pugixml.hpp>
#include <pybind11/stl.h>
namespace py = pybind11;
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

namespace tmx {
    class Layer;
    class Tileset;

    class Map final {
    public:
        explicit Map(const std::string& filename);
        unsigned getWidth() const;
        unsigned getHeight() const;
        unsigned getTileWidth() const;
        unsigned getTileHeight() const;
        const std::vector<Tileset>& getTilesets() const;
        const std::vector<Layer>& getLayers() const;

    private:
        pugi::xml_document _doc;
        unsigned _width, _height,
            _tileWidth, _tileHeight;
        std::vector<Tileset> _tilesets;
        std::vector<Layer> _layers;
    };

    class Tileset final {
    public:
        explicit Tileset(const Map& map, const pugi::xml_node& tilesetNode);
        unsigned getFirstGid() const;
        const std::string& getName() const;
        unsigned getTileWidth() const;
        unsigned getTileHeight() const;
        unsigned getSpacing() const;
        unsigned getMargin() const;
        unsigned getTileCount() const;
        unsigned getColumns() const;
        const sf::Texture& getTexture() const;

    private:
        unsigned _firstGid;
        std::string _name;
        unsigned _tileWidth, _tileHeight, _spacing,
            _margin, _tileCount, _columns;
        sf::Texture _texture;
    };

    class Tile;
    class Object;

    class Layer final : public sf::Drawable {
    public:
        enum class Type {
            Tile,
            Object,
            Image
        };

        explicit Layer(const Map& map, const pugi::xml_node& layerNode);
        const std::string& getName() const;
        Type getType() const;
        const std::vector<Tile>& getTiles() const;
        const std::vector<Object>& getObjects() const;

    private:
        std::string _name;
        Type _type;
        std::vector<Tile> _tiles;
        std::vector<Object> _objects;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    class Tile final : public sf::Sprite {
    public:
        explicit Tile(const Map& map, unsigned gid);
        unsigned getGid() const;

    private:
        unsigned _gid;
    };

    class Object final {
    public:
        explicit Object(const Map& map, const pugi::xml_node& objectNode);
        const std::string& getName() const;
        const std::string& getType() const;
        const Tile* getTile() const;
        const sf::IntRect& getRect() const;

    private:
        std::string _name, _type;
        std::shared_ptr<Tile> _tile;
        sf::IntRect _rect;
    };
}

void init_tmx(py::module& m);
