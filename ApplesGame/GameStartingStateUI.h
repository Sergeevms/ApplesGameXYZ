#pragma once
#include <SFML/Graphics.hpp>
namespace ApplesGame
{
	class GameStartingStateUI
	{
		sf::Text gameModeSelectText;
	public:
		void Init(sf::Font& textFont);
		void Draw(sf::RenderWindow& window) const;
	};
}