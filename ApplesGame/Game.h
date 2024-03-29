#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Constants.h"
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
		Pop,
		ClearStackAndPush
	};

	using StateMachineSwitch = std::pair<GameStateChangeType, GameState>;

	class Game
	{		
		// Global game data;
		std::vector<GameStateBase *> gameStateStack;
		std::queue<StateMachineSwitch> gameStateSwitchQueue;
		bool isGameWinned{ false };
		bool isShuttingDown{ false };
		int finiteApplesCount; //fixed apples count for finite apple game modes
		int numEatenApples{ 0 };
		sf::SoundBuffer appleEatenSoundBuffer;
		sf::SoundBuffer playerDeathSoundBuffer;

		sf::Sound appleEatenSound;
		sf::Sound playerDeathSound;

		std::unordered_map<GameModes, std::unordered_map<std::string, int>> recordTableData;
		GameModes currentGameMode{ GameModes::FiniteApplesWithoutAcceleration };

		// Resources
		sf::Font font;

		void InitRecordTablesData();

		void PushGameState(GameState newState, GameState previousState);
		void PopGameState();
		void UpdateGameState();
	public:
		Game();
		~Game();
		void Update(const float deltaTime);
		void Draw(sf::RenderWindow& window);
		void setCurrentGameMode(GameModes gameMode);
		bool IsGameShuttingDown() const;
		void Shutdown();
		void AddGameStateSwitchIfQueueEmpty(StateMachineSwitch machineSwitch);
		void SetGameWinnedState(bool currentGameWinned);
		void SetGameApplesEaten(int applesEaten);
		int GetGameApplesEaten() const;
		bool GetIsGameWined() const;
		GameModes GetCurrentGameMode() const;
		GameStateBase* GetCurrentGameState();
	};
		
}