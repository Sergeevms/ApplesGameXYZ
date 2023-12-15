#include <sstream>
#include <iomanip>
#include "UI.h"
#include "Game.h"
#include "Constants.h"


namespace ApplesGame
{
	void InitUI(UIState& uiState, const sf::Font& font)
	{
		//Exit text init
		uiState.hintText.setFont(font);
		uiState.hintText.setString("Press Esc to exit game\nRight, Up, Left, Down arrow\nto change player direction\nSpace to restart.");
		uiState.hintText.setPosition(0.f, 0.f);
		uiState.hintText.setFillColor(sf::Color::White);
		uiState.hintText.setCharacterSize(15);

		// Init game restart text
		uiState.restartText.setFont(font);
		uiState.restartText.setCharacterSize(25);

		//Game over text init;
		uiState.gameOverText.setFont(font);
		uiState.gameOverText.setCharacterSize(40);

		//Init score text
		uiState.scoreText.setFont(font);
		uiState.scoreText.setFillColor(sf::Color::Green);
		uiState.scoreText.setCharacterSize(20);

		//Init game over score text
		uiState.gameOverScoreText.setFont(font);
		uiState.gameOverScoreText.setFillColor(sf::Color::Green);
		uiState.gameOverScoreText.setCharacterSize(25);
		uiState.gameOverText.setStyle(sf::Text::Bold);

		//Init choosing gamemode text
		uiState.gameModeChoosingText.setFont(font);
		uiState.gameModeChoosingText.setCharacterSize(30);
		uiState.gameModeChoosingText.setFillColor(sf::Color::White);
		uiState.gameModeChoosingText.setStyle(sf::Text::Italic);
		uiState.gameModeChoosingText.setString({ "Press num key to choose game mode:\n\
1. infinite apples with player acceleration;\n\
2. infinite apples without player acceleration;\n\
3. finite apples with player acceleration;\n\
4. finite apples without player acceleration." });
		uiState.gameModeChoosingText.setPosition(SCREEN_WIDTH / 2.f - uiState.gameModeChoosingText.getGlobalBounds().width / 2.f,
			SCREEN_HEIGHT / 2.f - uiState.gameModeChoosingText.getGlobalBounds().height / 2.f);
	}

	void UpdateGameOveredStateUI(UIState& uiState, const Game& game)
	{
		std::stringstream gameRestartText = {};
		gameRestartText << "Game will restart in " << std::setprecision(2) << (RESTART_TIME - game.timeSinceGameOvered) << " seconds";
		uiState.restartText.setString(gameRestartText.str());
		uiState.restartText.setPosition(SCREEN_WIDTH / 2.f - uiState.restartText.getGlobalBounds().width / 2.f,
			SCREEN_HEIGHT / 2.f + uiState.gameOverText.getGlobalBounds().height);
		uiState.gameOverScoreText.setString("Your score: " + std::to_string(game.numEatenApples));
		uiState.gameOverScoreText.setPosition(SCREEN_WIDTH / 2.f - uiState.gameOverScoreText.getGlobalBounds().width / 2.f,
			SCREEN_HEIGHT / 2.f - uiState.gameOverText.getGlobalBounds().height / 2.f - uiState.gameOverScoreText.getGlobalBounds().height);
	}

	void UpdateGamePlayingStateUI(UIState& uiState, const Game& game)
	{
		uiState.scoreText.setString("Score : " + std::to_string(game.numEatenApples));
		uiState.scoreText.setPosition(SCREEN_WIDTH - uiState.scoreText.getGlobalBounds().width, 0);
	}

	void SetGameOveredTypeStateUI(UIState& uiState, const short gameState)
	{
		if (!(gameState & Game::GameState::IsGameWinned))
		{
			uiState.gameOverText.setString("GAME OVER");
			uiState.gameOverText.setFillColor(sf::Color::Red);
			uiState.gameOverText.setPosition(SCREEN_WIDTH / 2.f - uiState.gameOverText.getGlobalBounds().width / 2.f,
				SCREEN_HEIGHT / 2.f - uiState.gameOverText.getGlobalBounds().height / 2.f);
		}
		else
		{
			uiState.gameOverText.setString("YOU WIN");
			uiState.gameOverText.setFillColor(sf::Color::Cyan);
			uiState.gameOverText.setPosition(SCREEN_WIDTH / 2.f - uiState.gameOverText.getGlobalBounds().width / 2.f,
				SCREEN_HEIGHT / 2.f - uiState.gameOverText.getGlobalBounds().height / 2.f);
		}
	}

	void DrawUI(const UIState& uiState, sf::RenderWindow& window, const short gameState)
	{
		window.draw(uiState.hintText);
		if (!(gameState & Game::GameState::IsGameRestarting))
		{
			window.draw(uiState.scoreText);
			if (gameState & Game::GameState::IsGameOvered)
			{
				window.draw(uiState.restartText);
				window.draw(uiState.gameOverText);
				window.draw(uiState.gameOverScoreText);
			}
		}
		else
		{
			window.draw(uiState.gameModeChoosingText);
		}
	}
}