#include "GameStartingStateUI.h"
#include "Constants.h"

namespace ApplesGame
{
	void GameStartingStateUI::Init(sf::Font& textFont)
	{
		gameModeSelectText.setFont(textFont);
		gameModeSelectText.setCharacterSize(30);
		gameModeSelectText.setFillColor(sf::Color::White);
		gameModeSelectText.setStyle(sf::Text::Italic);
		gameModeSelectText.setString({ "Press num key to choose game mode:\n\
1. infinite apples with player acceleration;\n\
2. infinite apples without player acceleration;\n\
3. finite apples with player acceleration;\n\
4. finite apples without player acceleration." });
		gameModeSelectText.setPosition(SCREEN_WIDTH / 2.f - gameModeSelectText.getGlobalBounds().width / 2.f,
			SCREEN_HEIGHT / 2.f - gameModeSelectText.getGlobalBounds().height / 2.f);
	}

	void GameStartingStateUI::Draw(sf::RenderWindow& window) const
	{
		window.draw(gameModeSelectText);
	}
}