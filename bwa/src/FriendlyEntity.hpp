#pragma once
#include <SFML/Graphics.hpp>
#include "EntityBase.hpp"

namespace bwa {
	class FriendlyEntity : public EntityBase {
	public:
		FriendlyEntity();
		FriendlyEntity(sf::Texture &texture, sf::IntRect &texture_rect);

		void animateLeft();
		void animateRight();
		void animateUp();
		void animateDown();
		void setPosition(float x, float y);
		void draw(sf::RenderWindow &window);
	};
}