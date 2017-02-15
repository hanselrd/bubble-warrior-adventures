#include "Tmx.hpp"
#include <cppcodec/base64_default_rfc4648.hpp>
#include <stdexcept>

tmx::Map::Map(const std::string& filename) {
	auto success = _doc.load_file(filename.c_str());

	if (success) {
		auto mapNode = _doc.child("map");
		if (mapNode.empty())
			throw std::runtime_error("Map node is missing");

		_width = mapNode.attribute("width").as_uint();
		_height = mapNode.attribute("height").as_uint();
		_tilewidth = mapNode.attribute("tilewidth").as_uint();
		_tileheight = mapNode.attribute("tileheight").as_uint();
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
	return _tilewidth;
}

unsigned tmx::Map::getTileHeight() const {
	return _tileheight;
}

const std::vector<std::shared_ptr<tmx::Layer>>& tmx::Map::getLayers() const {
	return _layers;
}
