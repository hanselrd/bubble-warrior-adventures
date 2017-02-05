#pragma once
#include <SFML/Graphics.hpp>

namespace bwa {
	class EntityBase {
	public:
		virtual void animateLeft() = 0;
		virtual void animateRight() = 0;
		virtual void animateUp() = 0;
		virtual void animateDown() = 0;
		virtual void draw(sf::RenderWindow &window) = 0;
	protected:
		int _damage;
		int _health;
		int _x_coordinate;
		int _y_coordinate;
		sf::Texture _texture;
		sf::Sprite _sprite;
	};
}