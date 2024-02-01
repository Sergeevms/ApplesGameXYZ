#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	class Game;

	class Rock
	{
		Position2D position;
		sf::Sprite sprite;
	public:		
		void InitRock(const sf::Texture& rockTexture);
		void Draw(sf::RenderWindow& window);

		//set rock position to position; 
		//return true if rock don't collide with noRockRectangle, false else
		bool TryToSetRockPosition(const Rectangle& noRockRectangle, const Position2D position);
		Rectangle getCollider();
	};	
}
