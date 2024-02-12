#pragma once
#include <SFML/Graphics.hpp>
namespace ApplesGame
{
	class GamePlayingStateUI
	{
		class HintUI
		{
			sf::Text text;
		public:
			HintUI(const sf::Font& font);
			void Start(const sf::Font& font);
			void Draw(sf::RenderWindow& window) const;
		};

		class CurrentScoreUI
		{
			sf::Text text;
		public:
			CurrentScoreUI(const sf::Font font);
			void Draw(sf::RenderWindow& window) const;
			void UpdatePlayerScore(int newPlayerScore);
		};
	};
}