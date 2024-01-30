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
#include "AppleColiderGrid.h"

namespace ApplesGame
{
	enum class GameState
	{
		None = 0,
		Starting,
		Playing,
		GameOvered,
		RecordTable
	};

	enum GameOptions
	{
		InfiniteApples = 1,
		WithAcceleration = 1 << 1
	};

	enum GameModes
	{
		FiniteApplesWithoutAcceleration = 0,
		InfinteApplesWithoutAcceleration = GameOptions::InfiniteApples,
		FiniteApllesWithAcceleration = GameOptions::WithAcceleration,
		InfiniteApplesWithAcceleartion = GameOptions::InfiniteApples | GameOptions::WithAcceleration
	};

	class Game
	{
		Player player;
		ApplesMassive apples;
		std::vector<Rock> rocks;
		Rectangle windowRectangle;
		Rectangle noRocksRectangle;
		AppleColliderGrid appleCollderGrid;
		sf::RenderWindow* window;

		// Global game data;
		std::vector<GameState> gameStateStack;
		GameModes gameMode;
		bool gameWinned;
		int finiteApplesCount; //fixed apples count for finite apple game modes
		int numEatenApples;
		float gameStateTimer;
		UI gameUI;

		// Resources
		sf::Font font;
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		sf::SoundBuffer appleEatenSoundBuffer;
		sf::SoundBuffer playerDeathSoundBuffer;

		sf::Sound appleEatenSound;
		sf::Sound playerDeathSound;


		void PushGameState(GameState state);
		void PopGameState();
		void SwitchGameState(GameState newState);
		void SwitchGameStateInternal(GameState oldState, GameState newState);

		void InitGameStartingState();
		void UpdateGameStartingState();
		void EndGameStartingState();

		void InitGamePlayingState();
		void UpdateGamePlayingState(const float deltaTime);
		void EndGamePlayingState();

		void InitGameOveredState();
		void UpdateGameOveredState(const float deltaTime);
		void EndGameOveredState();

		void InitGameRecordTableState();
		void UpdateGameRecordTableState(const float deltaTime);
		void EndGameRecordTableState();

	public:
		void Init();
		void Update(const float deltaTime);
		void Draw(sf::RenderWindow& window);
		void ShutdownGame();

		GameState GetCurrentGameState();
	};
		
}