#include "Tmx.hpp"
#include <cppcodec/base64_default_rfc4648.hpp>
#include <iostream>
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

		Tileset tileset(mapNode.child("tileset"));
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
		std::cout << "\t" << texture.getSize().x << " " << texture.getSize().y << std::endl;
	}

	/*pugi::xml_document doc;
	auto result = doc.load_file("assets/maps/world.tmx");
	if (result) {
		for (const auto& node : doc.child("map")) {
			std::cout << node.attribute("name").as_string() << std::endl;
		}
	}

	for (const auto& layer : doc.child("map").children("layer")) {
	std::string data = layer.child("data").child_value();
	data.erase(std::remove_if(std::begin(data), std::end(data), std::bind(std::isspace<char>, std::placeholders::_1, std::locale::classic())), std::end(data));
	std::vector<std::uint8_t> decoded = base64::decode(data);
	std::vector<std::uint32_t> gids(decoded.size() / 4);
	std::memcpy(gids.data(), decoded.data(), decoded.size());
	for (auto &gid : gids)
	std::cout << gid << " ";
	std::cout << std::endl;
	}
	auto map = doc.child("map");
	for (const auto& it : map) {
	std::cout << it.attribute("name").as_string() << std::endl;
	}*/
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

const std::vector<std::shared_ptr<tmx::Layer>>& tmx::Map::getLayers() const {
	return _layers;
}

tmx::Tileset::Tileset(const pugi::xml_node& tilesetNode) {
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
