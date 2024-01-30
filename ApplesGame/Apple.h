#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	class Game;

	class Apple
	{
		Position2D applePosition;
		sf::Sprite sprite;
	public:
		Apple(const sf::Texture& appleTexture);
		void DrawApple(sf::RenderWindow& window);
		void SetPosition(const Position2D applePosition);
		const Position2D& GetPosition() const;
		Circle GetCollider();
	};	
}