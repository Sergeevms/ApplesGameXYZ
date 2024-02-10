#pragma once
#include<SFML/Graphics.hpp>

#include "Math.h"

namespace ApplesGame
{
	enum class TextAlignment
	{
		left,
		center,
		right
	};

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

	void DrawText(std::vector<sf::Text*>& texts, Position2D leftUpCorner, TextAlignment alignment, Vector2D spacing, sf::RenderWindow& window);
}