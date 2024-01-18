#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "ApplesMassive.h"
#include "Rock.h"
#include "UI.h"
#include "Math.h"
#include "Constants.h"
#include "RecordTable.h"

namespace ApplesGame
{
	struct Game
	{
		enum GameState //enumeration for using gameState bitmap
		{
			IsInfiniteApples = 1,
			IsWithAcceleration = 1 << 1,
			IsGameOvered = 1 << 2,
			IsGameRestarting = 1 << 3,
			IsGameWinned = 1 << 4,
			IsRecordTableShowing = 1 << 5
		};

		enum GameModes
		{
			FiniteApplesWithoutAcceleration = 0,
			InfinteApplesWithoutAcceleration = GameState::IsInfiniteApples,
			FiniteApllesWithAcceleration = GameState::IsWithAcceleration,
			InfiniteApplesWithAcceleartion = GameState::IsInfiniteApples | GameState::IsWithAcceleration
		};

		const static short gameModeBitmask = (1 << 2) - 1;

		Player player;
		ApplesMassive apples;
		Rock rocks[NUM_ROCKS];
		Rectangle windowRectangle;
		Rectangle noRocksRectangle;

		// Global game data;
		short gameState; // bitmap for current mode and gamestate (game overed, playing, restarting)
		int finiteApplesCount; //fixed apples count for finite apple game modes
		int numEatenApples;
		float gameOveredTimer;
		UIState uiState;

		// Resources
		sf::Font font;
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		sf::SoundBuffer appleEatenSoundBuffer;
		sf::SoundBuffer playerDeathSoundBuffer;

		sf::Sound appleEatenSound;
		sf::Sound playerDeathSound;
	};

	void InitGame(Game& game);
	void StartGameStartingState(Game& game);
	void StartGamePlayingState(Game& game);
	void StartGameOveredState(Game& game);
	void StartGameRecordTableState(Game& game);
	void UpdateGame(Game& game, const float deltaTime);
	void UpdateGameRecordTableState(Game& game, const float deltaTime);
	void UpdateGameStartingState(Game& game);
	void UpdateGamePlayingState(Game& game, const float deltaTime);
	void UpdateGameOveredState(Game& game, const float deltaTime);
	void DrawGame(sf::RenderWindow& window, Game& game);
}