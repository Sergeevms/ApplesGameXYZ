#include <sstream>
#include <iomanip>
#include "UI.h"
#include "Game.h"
#include "Constants.h"


namespace ApplesGame
{
	void HintUI::Init(const sf::Font& font)
	{
		text.setFont(font);
		text.setPosition(0.f, 0.f);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(15);
	}

	void HintUI::Draw(sf::RenderWindow& window) const
	{
		window.draw(text);
	}

	void HintUI::SetState(GameState gameState)
	{
		switch (gameState)
		{		
		case ApplesGame::GameState::Playing:
			text.setString("Press Esc to exit game\nRight, Up, Left, Down arrow\nto change player direction\nSpace to restart.");
			break;
		default:
			text.setString("Press Esc to exit game\nSpace to restart.");
			break;
		}
	}

	void GameOverUI::Init(const sf::Font& font)
	{
		baseText.setFont(font);
		baseText.setCharacterSize(40);
		baseText.setStyle(sf::Text::Bold);
		scoreText.setFont(font);
		scoreText.setFillColor(sf::Color::Green);
		scoreText.setCharacterSize(25);
	}

	void GameOverUI::Draw(sf::RenderWindow& window) const
	{
		window.draw(baseText);
		window.draw(scoreText);
	}

	void GameOverUI::UpdateTextByGameResult(bool gameWinned, int score)
	{
		if (gameWinned)
		{
			baseText.setString("YOU WIN");
			baseText.setFillColor(sf::Color::Cyan);
			baseText.setPosition(SCREEN_WIDTH / 2.f - baseText.getGlobalBounds().width / 2.f,
				SCREEN_HEIGHT / 2.f - baseText.getGlobalBounds().height / 2.f);
		}
		else
		{
			baseText.setString("GAME OVER");
			baseText.setFillColor(sf::Color::Red);
			baseText.setPosition(SCREEN_WIDTH / 2.f - baseText.getGlobalBounds().width / 2.f,
				SCREEN_HEIGHT / 2.f - baseText.getGlobalBounds().height / 2.f);
		}
		scoreText.setString("Your score: " + std::to_string(score));
		scoreText.setPosition(SCREEN_WIDTH / 2.f - baseText.getGlobalBounds().width / 2.f,
			SCREEN_HEIGHT / 2.f - baseText.getGlobalBounds().height / 2.f - scoreText.getGlobalBounds().height);
	}

	void RecordTableUI::Init(const sf::Font& font, std::ifstream& playerNamesInputStream, int finiteApplesCount)
	{
		timeText.setFont(font);
		timeText.setCharacterSize(15);
		timeText.setString("Game will automatically restart in ");
		headerText.setFont(font);
		headerText.setCharacterSize(40);
		headerText.setString("Press Space to restart game now");
		headerText.setPosition(SCREEN_WIDTH / 2.f - headerText.getGlobalBounds().width / 2.f,
			SCREEN_HEIGHT - headerText.getGlobalBounds().height - timeText.getGlobalBounds().height * 3);

		recordTables.reserve(GAME_MODES_COUNT);
		std::vector<std::string> initialPlayerNames;
		std::string currentPlayerName;
		while (std::getline(playerNamesInputStream, currentPlayerName))
		{
			initialPlayerNames.push_back(currentPlayerName);
		}

		for (int i = 0; i < GAME_MODES_COUNT; ++i)
		{
			recordTables.push_back(RecordTable(initialPlayerNames, RECORDS_TABLE_SIZE,
				GameOptions::InfiniteApples & i ? (int)(MAX_APPLES * RECORDS_TABLE_MAX_COEFFICIENT) : finiteApplesCount, font, i));
		}

	}

	void RecordTableUI::Draw(sf::RenderWindow& window, GameModes gameMode) const
	{		
		window.draw(timeText);
		window.draw(headerText);
		recordTables[gameMode].Draw(window);
	}

	void RecordTableUI::UpdateText(float timeSinceStateStarted)
	{
		std::stringstream gameRestartText = {};
		gameRestartText << "Game will automatically restart in " << std::setprecision(0) << std::fixed << (RECORD_TABLE_RESTART_TIME - timeSinceStateStarted) << " seconds";
		timeText.setString(gameRestartText.str());
		timeText.setPosition(SCREEN_WIDTH / 2.f - timeText.getGlobalBounds().width / 2.f, SCREEN_HEIGHT - timeText.getGlobalBounds().height * 2);
	}

	void RecordTableUI::UpdatePlayerScore(GameModes gameMode, int newPlayerScore)
	{
		recordTables[gameMode].UpdatePlayerScore(newPlayerScore);
	}

	void CurrentScoreUI::Init(const sf::Font& font)
	{
		text.setFont(font);
		text.setFillColor(sf::Color::Green);
		text.setCharacterSize(20);
	}

	void CurrentScoreUI::Draw(sf::RenderWindow& window) const
	{
		window.draw(text);
	}

	void CurrentScoreUI::UpdatePlayerScore(int currentScore)
	{
		text.setString("Score : " + std::to_string(currentScore));
		text.setPosition(SCREEN_WIDTH - text.getGlobalBounds().width, 0);
	}

	void GameModeSelectUI::Init(const sf::Font& font)
	{
		text.setFont(font);
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Italic);
		text.setString({ "Press num key to choose game mode:\n\
1. infinite apples with player acceleration;\n\
2. infinite apples without player acceleration;\n\
3. finite apples with player acceleration;\n\
4. finite apples without player acceleration." });
		text.setPosition(SCREEN_WIDTH / 2.f - text.getGlobalBounds().width / 2.f,
			SCREEN_HEIGHT / 2.f - text.getGlobalBounds().height / 2.f);
	}

	void GameModeSelectUI::Draw(sf::RenderWindow& window) const
	{
		window.draw(text);
	}	

	/*UI::UI(const sf::Font& font, std::ifstream& playerNameSource, int finiteApplesCount) : hintUI(font), gameOverUI(font),
		recordTableUI(RecordTableUI(font, playerNameSource, finiteApplesCount)), currentScoreUI(font), gameModeSelectUI(font)
	{		
		
	}*/

	void UI::Init(const sf::Font& font, std::ifstream& playerNamesInputStream, int finiteApplesCount)
	{
		hintUI.Init(font);
		gameOverUI.Init(font);
		currentScoreUI.Init(font);
		gameModeSelectUI.Init(font);
		recordTableUI.Init(font, playerNamesInputStream, finiteApplesCount);
	}

	void UI::Update(GameState gameState, int currentScore, const float time)
	{
		switch (gameState)
		{
		case GameState::Playing:
		{
			currentScoreUI.UpdatePlayerScore(currentScore);
		}
		case GameState::RecordTable:
		{
			recordTableUI.UpdateText(time);
		}
		}
	}

	void UI::UpdateStateChanged(GameState gameState, GameModes gameMode, const int score, bool gameIsWinned)
	{
		hintUI.SetState(gameState);
		switch (gameState)
		{
		case GameState::GameOvered:
		{
			gameOverUI.UpdateTextByGameResult(gameIsWinned, score);
			break;
		}
		case GameState::RecordTable:
		{
			recordTableUI.UpdatePlayerScore(gameMode, score);
			break;
		}
		}
	}

	void UI::Draw(sf::RenderWindow& window, GameState gameState, GameModes  gameMode)
	{
		hintUI.Draw(window);
		switch (gameState)
		{
		case GameState::Starting:
		{
			gameModeSelectUI.Draw(window);
			break;
		}
		case GameState::GameOvered:
		{
			gameOverUI.Draw(window);
			break;
		}
		case GameState::RecordTable:
		{
			recordTableUI.Draw(window, gameMode);
			break;
		}
		}
	}
}