#include "GameOveredStateUI.h"
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
	void GameOveredStateUI::Init(sf::Font& textFont, bool isGameWinned, int playerScore)
	{
		gameOverText.setFont(textFont);
		gameOverText.setCharacterSize(40);
		gameOverText.setStyle(sf::Text::Bold);
		scoreText.setFont(textFont);
		scoreText.setFillColor(sf::Color::Green);
		scoreText.setCharacterSize(25);
		hintText.setFont(textFont);
		hintText.setCharacterSize(20);
		hintText.setPosition(sf::Vector2f{ 0.f, 0.f });
		hintText.setString("Press Esc to go to main menu");

		if (isGameWinned)
		{
			gameOverText.setString("YOU WIN");
			gameOverText.setFillColor(sf::Color::Cyan);
		}
		else
		{
			gameOverText.setString("GAME OVER");
			gameOverText.setFillColor(sf::Color::Red);
		}
		gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		SetOriginByRelative(gameOverText, RelativeOrigin{ 0.5f, 0.5f });

		scoreText.setString("Your score: " + std::to_string(playerScore));
		SetOriginByRelative(scoreText, RelativeOrigin{ 0.5f, 0.f });
		scoreText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + gameOverText.getGlobalBounds().height + TEXT_SPACING);
	}

	void GameOveredStateUI::Draw(sf::RenderWindow& window) const
	{
		window.draw(gameOverText);
		window.draw(scoreText);
		window.draw(hintText);
	}
}