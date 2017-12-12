#pragma once
#include <pugixml.hpp>
#include <pybind11/pybind11.h>
namespace py = pybind11;
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "Object.hpp"

class Map final {
public:
    class Layer;
    class Tileset;

    explicit Map(const std::string& filename);
    unsigned getWidth() const; // tiles
    unsigned getHeight() const; // tiles
    unsigned getTileWidth() const; // pxls
    unsigned getTileHeight() const; // pxls
    sf::Vector2u getSize() const; // pxls
    const std::vector<Tileset>& getTilesets() const;
    const std::vector<Layer>& getLayers() const;

private:
    pugi::xml_document _doc;
    unsigned _width, _height,
        _tileWidth, _tileHeight;
    std::vector<Tileset> _tilesets;
    std::vector<Layer> _layers;

public:
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
        std::shared_ptr<sf::Texture> getTexture() const;

    private:
        unsigned _firstGid;
        std::string _name;
        unsigned _tileWidth, _tileHeight, _spacing,
            _margin, _tileCount, _columns;
        std::shared_ptr<sf::Texture> _texture;
    };

    class Tile;
    class Object;

    class Layer : public sf::Drawable {
    public:
        enum class Type {
            Tile,
            Object,
            NPC,
            Enemy,
            Item,
            Spawn,
            Portal,
            Image
        };

        explicit Layer(const Map& map, const pugi::xml_node& layerNode);
        const std::string& getName() const;
        Type getType() const;
        bool isVisible() const;
        const std::vector<Tile>& getTiles() const;
        const std::vector<Object>& getObjects() const;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::string _layerName;
        Type _type;
        bool _visible;
        std::vector<Tile> _tiles;
        std::vector<Object> _objects;
        
    };

    class Tile final : public sf::Drawable, public sf::Transformable {
    public:
        explicit Tile(const Map& map, unsigned gid);
        unsigned getGid() const;
        sf::FloatRect getBounds() const;
        void update();

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        unsigned _gid;
        sf::VertexArray _vertices;
        std::shared_ptr<sf::Texture> _texture;
    };

    class Object final : public ::Object {
    public:
        explicit Object(const Map& map, const pugi::xml_node& objectNode);
        const std::string& getName() const;
        const Object::EntityType& getType() const;
        const sf::IntRect& getRect() const;
        sf::FloatRect getLocalBounds() const override;

        //const std::vector<Entity>& getNPCs() const;
        //const std::vector<Entity>& getItems() const;
        //const std::vector<Entity>& getEnemies() const;
        //const std::vector<Entity>& getSpawn() const;
        //const std::vector<Entity>& getPortal() const;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::string _tempName, _tempType;
        std::shared_ptr<Tile> _tile;
        sf::IntRect _rect;
    };
};

void initMap(py::module& m);
