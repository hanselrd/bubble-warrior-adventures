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
		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;

		/*
			Width of the map in tiles
		*/
		unsigned getWidth() const;

		/*
			Height of the map in tiles
		*/
		unsigned getHeight() const;

		/*
			Width of a tile in pixels
		*/
		unsigned getTileWidth() const;

		/*
			Height of a tile in pixels
		*/
		unsigned getTileHeight() const;

		/*
			Gets all the layers in order
		*/
		const std::vector<std::shared_ptr<Layer>>& getLayers() const;

	private:
		pugi::xml_document _doc;
		unsigned _width, _height, _tilewidth, _tileheight;
		std::vector<std::shared_ptr<Layer>> _layers;
	};
}
