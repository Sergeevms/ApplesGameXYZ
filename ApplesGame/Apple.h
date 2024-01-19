#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Game;

	struct Apple
	{
		Position2D applePosition;
		sf::Sprite sprite;
	};

	void InitApple(Apple& apple, const Game& game);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	void SetApplePosition(Apple& apple, const Position2D applePosition);
	Position2D GetPosition(const Apple& apple);
	Circle GetAppleCollider(const Apple& apple);
}