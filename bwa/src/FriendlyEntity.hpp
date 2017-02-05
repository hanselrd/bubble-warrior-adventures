#pragma once
#include <SFML/Graphics.hpp>
#include "EntityBase.hpp"

namespace bwa {
	class FriendlyEntity : public EntityBase {
	public:
		// Constructors
		FriendlyEntity();
		FriendlyEntity(sf::Texture &texture, sf::IntRect &texture_rect);

		// General functions
		void setPosition(float x, float y);

		// Animation functions
		void animateLeft();
		void animateRight();
		void animateUp();
		void animateDown();
		void animateStanding();

		// Window functions
		void draw(sf::RenderWindow &window);
	};
}