#pragma once
#include <SFML/Graphics.hpp>
#include "EntityBase.hpp"

namespace bwa {
	class FriendlyEntity : public EntityBase {
	public:
		FriendlyEntity(sf::Texture &texture);
		void animateLeft();
		void animateRight();
		void animateUp();
		void animateDown();
		void draw(sf::RenderWindow &window);
	};
}