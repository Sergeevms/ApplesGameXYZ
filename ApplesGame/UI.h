#pragma once
#include <SFML/Graphics.hpp>
#include "RecordTable.h"

namespace ApplesGame
{
	struct Game;

	struct UIState
	{
		sf::Text hintText;
		sf::Text gameOverText;
		sf::Text recordTableRestartTimeText;
		sf::Text recordTableRestartText;
		sf::Text scoreText;
		sf::Text gameOverScoreText;
		sf::Text gameModeChoosingText;
		std::vector<RecordTable> recordTables;
	};

	void InitUI(UIState& uiState, const sf::Font& font);
	void UpdateRecordTable(UIState& uiState, const Game& game);
	void UpdateGamePlayingStateUI(UIState& uiState, const Game& game);
	void UpdateRecordTableStateUI(UIState& uiState, const Game& game);

	void UpdatePlayerRecord(UIState& uiState, const Game& game);
	void SetGameOveredTypeStateUI(UIState& uiState, const Game& game);

	void DrawUI(UIState& uiState, sf::RenderWindow& window, const short gameState);
}