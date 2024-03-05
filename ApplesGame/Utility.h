#pragma once
#include<SFML/Graphics.hpp>

#include "Math.h"

namespace ApplesGame
{
	enum class Alignment
	{
		Min,
		Middle,
		Max
	};

	enum class Orientation
	{
		Vertical,
		Horizontal
	};

	void DrawTexts(sf::RenderWindow& window, std::vector<sf::Text*> const& texts, Position2D position, RelativeOrigin relativeOrigin,
		Alignment alignment, Orientation orientation, float spacing = 0);

	template<sf::Keyboard::Key key> bool KeyPressed()
	{
		static bool wasPressed = false;
		if (sf::Keyboard::isKeyPressed(key) == false)
		{
			return wasPressed = false;
		}
		else
		{
			return sf::Keyboard::isKeyPressed(key) && wasPressed ? false : wasPressed = true;
		}
	};
}