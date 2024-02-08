#pragma once
#include<SFML/Graphics.hpp>

namespace ApplesGame
{
	template<sf::Keyboard::Key T> bool KeyPressed()
	{
		static bool WasPressed = false;
		if (sf::Keyboard::isKeyPressed(T) == false)
		{
			return WasPressed = false;
		}
		else
		{
			return sf::Keyboard::isKeyPressed(T) && WasPressed ? false : WasPressed = true;
		}
	};
}