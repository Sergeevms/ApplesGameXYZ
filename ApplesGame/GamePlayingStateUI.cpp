#include "GamePlayingStateUI.h"
#include "Constants.h"

void ApplesGame::GamePlayingStateUI::Init(sf::Font& textFont)
{
	hintText.setFont(textFont);
	hintText.setPosition(0.f, 0.f);
	hintText.setFillColor(sf::Color::White);
	hintText.setCharacterSize(15);


	currentScoreText.setFont(textFont);
	currentScoreText.setFillColor(sf::Color::Green);
	currentScoreText.setCharacterSize(20);
}

void ApplesGame::GamePlayingStateUI::Draw(sf::RenderWindow& window) const
{
	window.draw(hintText);
	window.draw(currentScoreText);
}

void ApplesGame::GamePlayingStateUI::UpdatePlayerScore(int newPlayerScore)
{
	currentScoreText.setString("Score : " + std::to_string(newPlayerScore));
	currentScoreText.setPosition(SCREEN_WIDTH - currentScoreText.getGlobalBounds().width, 0);
}
