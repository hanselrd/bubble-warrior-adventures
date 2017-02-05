#pragma once
#include <SFML/Graphics.hpp>

namespace bwa {
	class EntityBase {
	public:
		// Animation Functions
		virtual void animateLeft() = 0;
		virtual void animateRight() = 0;
		virtual void animateUp() = 0;
		virtual void animateDown() = 0;

		// Window Functions
		virtual void draw(sf::RenderWindow &window) = 0;
	protected:
		int _damage;
		int _health;
		bool _invincible; // True means yes
		float _movement_speed;
		float _x_coordinate;
		float _y_coordinate;

		// SFML members
		sf::Clock _clock;
		sf::Sprite _sprite;
		sf::Texture _texture;
	};
}