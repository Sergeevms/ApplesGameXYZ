#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Game;

	struct Rock
	{
		Position2D rockPosition;
		sf::Sprite sprite;
	};

	void InitRock(Rock& rock, const Game& game);
	void DrawRock(Rock& rock, sf::RenderWindow& window);

	//set rock position to position; 
	//return true if rock don't collide with noRockRectangle, false else
	bool TryToSetRockPosition(Rock& rock, const Rectangle& noRockRectangle, const Position2D position);
	Rectangle getRockCollider(const Rock& rock);
}
