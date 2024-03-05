#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	class ReturnToMenuDialogStateUI
	{
		sf::Text returnToMainMenuText;
		sf::Text hintText;
		sf::Text buttonToPressText;
	public:
		void Init(sf::Font& textFont);
		void Draw(sf::RenderWindow& window);
	};
}