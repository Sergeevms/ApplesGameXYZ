#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Game;

	struct UIState
	{
		sf::Text hintText;
		sf::Text gameOverText;
		sf::Text restartText;
		sf::Text scoreText;
		sf::Text gameOverScoreText;
		sf::Text gameModeChoosingText;
	};

	void InitUI(UIState& uiState, const sf::Font& font);
	void UpdateGameOveredStateUI(UIState& uiState, const Game& game);
	void UpdateGamePlayingStateUI(UIState& uiState, const Game& game);
	void SetGameOveredTypeStateUI(UIState& uiState, const short gameState);
	void DrawUI(const UIState& uiState, sf::RenderWindow& window, const short gameState);
}