#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "ApplesMassive.h"
#include "Rock.h"
#include "UI.h"
#include "Math.h"
#include "Constants.h"

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
			IsGameWinned = 1 << 4
		};

		Player player;
		ApplesMassive apples;
		Rock rocks[NUM_ROCKS];
		Rectangle windowRectangle;
		Rectangle noRocksRectangle;

		// Global game data
		short gameState; // bitmap for current mode and gamestate (game overed, playing, restarting)
		int numEatenApples;
		float timeSinceGameOvered;
		bool isGameOvered;
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

	void StartGameStartingState(Game& game);
	void StartGamePlayingState(Game& game);
	void InitGame(Game& game);
	void StartGameOveredState(Game& game);
	void UpdateGame(Game& game, const float deltaTime);
	void UpdateGameStartingState(Game& game);
	void UpdateGamePlayingState(Game& game, const float deltaTime);
	void UpdateGameOveredState(Game& game, const float deltaTime);
	void DrawGame(sf::RenderWindow& window, Game& game);
}