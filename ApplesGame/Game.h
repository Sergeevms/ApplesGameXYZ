#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <queue>
#include "Player.h"
#include "ApplesMassive.h"
#include "Rock.h"
#include "UI.h"
#include "Math.h"
#include "Constants.h"
#include "RecordTable.h"
#include "AppleColiderGrid.h"
#include "GameStateBase.h"

namespace ApplesGame
{
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

	enum class GameStateChangeType
	{
		Switch,
		Push,
		Pop
	};

	using StateMachineSwitch = std::pair<GameStateChangeType, GameState>;

	class Game
	{		
		// Global game data;
		std::vector<GameState *> gameStateStack;
		std::queue<StateMachineSwitch> gameStateSwitchQueue;
		bool isGameWinned;
		UI gameUI;
		int finiteApplesCount; //fixed apples count for finite apple game modes
		int numEatenApples;
		GameModes currentGameMode;

		// Resources
		sf::Font font;


		void PushGameState(GameState state);
		void PopGameState();
		void SwitchGameState(GameState newState);
		void SwitchGameStateInternal(GameState oldState, GameState newState);

		void InitGameOveredState();
		void UpdateGameOveredState(const float deltaTime);
		void EndGameOveredState();

		void InitGameRecordTableState();
		void UpdateGameRecordTableState(const float deltaTime);
		void EndGameRecordTableState();

		void InitGameEscapeDialog();
		void UpdateGameEscapeDialog();
		void EndGameEscapeDialog();

	public:
		void Init();
		void Update(const float deltaTime);
		void Draw(sf::RenderWindow& window);
		bool IsGameShuttingDown();
		void TryToAddGameStateSwitchToQueue(StateMachineSwitch&&);
		void SetGameWinnedState(bool currentGameWinned);
		void SetCurrentGameApplesEaten(int applesEaten);
		void setCurrentGameMode(GameModes gameMode);

		GameState GetCurrentGameState();
	};
		
}