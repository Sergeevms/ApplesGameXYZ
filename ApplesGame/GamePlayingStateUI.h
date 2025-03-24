#pragma once
#include <SFML/Graphics.hpp>
namespace ApplesGame
{
	class GamePlayingStateUI
	{
		sf::Text hintText;
		sf::Text currentScoreText;
	public:
		void Init(sf::Font& textFont);
		void Draw(sf::RenderWindow& window) const;
		void UpdatePlayerScore(int newPlayerScore);
	};
}