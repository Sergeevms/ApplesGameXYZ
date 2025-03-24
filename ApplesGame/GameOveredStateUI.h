#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	class GameOveredStateUI
	{
		sf::Text gameOverText;
		sf::Text scoreText;
		sf::Text hintText;
	public:
		void Init(sf::Font& textFont, bool isGameWinned, int playerScore);
		void Draw(sf::RenderWindow& window) const;
	};
}