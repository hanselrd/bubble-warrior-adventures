#pragma once
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
#include <string>

namespace bwa {
	namespace tmx {
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

		private:
			pugi::xml_document _doc;
			unsigned _width, _height, _tilewidth, _tileheight;
		};
	}
}