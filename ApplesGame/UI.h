#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "RecordTable.h"

namespace ApplesGame
{
	class Game;
	enum class GameState;
	enum GameModes;

	class HintUI
	{
		bool isPlayingState;
		sf::Text text;
	public:
		void Init(const sf::Font& font);
		void Draw(sf::RenderWindow& window) const;
		void SetState(GameState gameState);
	};

	class GameOverUI
	{
		bool isGameWinned;
		sf::Text baseText;
		sf::Text scoreText;
	public:
		void Init(const sf::Font& font);
		void Draw(sf::RenderWindow& window) const;
		void UpdateTextByGameResult(bool gameWinned, int score);
	};

	class RecordTableUI
	{
		sf::Text timeText;
		sf::Text headerText;
		std::vector<RecordTable> recordTables{};
	public:				
		void Init(const sf::Font& font, std::ifstream& playerNamesInputStream, int finiteApplesCount);
		void Draw(sf::RenderWindow& window, GameModes gameMode) const;
		void UpdateText(float timeSinceStateStarted);
		void UpdatePlayerScore(GameModes gameMode, int newPlayerScore);
	};

	class CurrentScoreUI
	{
		sf::Text text;
	public:
		void Init(const sf::Font& font);
		void Draw(sf::RenderWindow& window) const;
		void UpdatePlayerScore(int newPlayerScore);
	};

	class GameModeSelectUI
	{
		sf::Text text;
	public:
		void Init(const sf::Font& font);
		void Draw(sf::RenderWindow& window) const;
	};

	class UI
	{
		HintUI hintUI;
		GameOverUI gameOverUI;
		RecordTableUI recordTableUI;
		CurrentScoreUI currentScoreUI;
		GameModeSelectUI gameModeSelectUI;

	public:
		//UI(const sf::Font& font, std::ifstream& playerNamesInputStream, int finiteApplesCount);
		void Init(const sf::Font& font, std::ifstream& playerNamesInputStream, int finiteApplesCount);
		void Update(GameState gameState, int currentScore, const float time);
		void UpdateStateChanged(GameState gameState, GameModes gameMode, const int score, bool gameIsWinned);
		void Draw(sf::RenderWindow& window, GameState gameState, GameModes gameMode);
	};	
}