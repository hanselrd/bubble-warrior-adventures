#pragma once
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

namespace tmx {
	class Layer;

	class Map final {
	public:
		explicit Map(const std::string& filename);
		unsigned getWidth() const;
		unsigned getHeight() const;
		unsigned getTileWidth() const;
		unsigned getTileHeight() const;
		const std::vector<std::shared_ptr<Layer>>& getLayers() const;

	private:
		pugi::xml_document _doc;
		unsigned _width, _height,
			_tileWidth, _tileHeight;
		std::vector<std::shared_ptr<Layer>> _layers;
	};

	class Tileset final {
	public:
		explicit Tileset(const pugi::xml_node& tilesetNode);
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

	/*
		Base class for all layers:
		Tile, Object and Image
	*/
	class Layer {
	public:
		enum class Type {
			Tile,
			Object,
			Image
		};

		explicit Layer(const pugi::xml_node& layerNode);
		const std::string& getName() const;
		Type getType() const;

	private:
		std::string _name;
		Type _type;
	};

	class Tile;

	class TileLayer final : public Layer, public sf::Drawable {
	public:
		explicit TileLayer(const pugi::xml_node& tileLayerNode);
		unsigned getWidth() const;
		unsigned getHeight() const;
		const std::vector<Tile>& getTiles() const;

	private:
		unsigned _width, _height;
		std::vector<Tile> _tiles;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

	class Object;

	class ObjectLayer final : public Layer, public sf::Drawable {
	public:
		explicit ObjectLayer(const pugi::xml_node& objectLayerNode);
		const std::vector<Object>& getObjects() const;
		
	private:
		std::vector<Object> _objects;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}
