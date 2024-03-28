#include <assert.h>
#include <fstream>
#include <list>
#include "Game.h"
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Utility.h"
#include "ReturnToMenuDialogState.h"
#include "GameStartingState.h"
#include "GameRecordsTableState.h"
#include "GamePlayingState.h"
#include "GameOveredState.h"
#include "MainMenuState.h"


namespace ApplesGame
{
	Game::Game()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));

		//Get apples count for finite apple game modes
		finiteApplesCount = GetRandomIntInRange(MIN_APPLES, MAX_APPLES);
		assert(appleEatenSoundBuffer.loadFromFile(RESOURCES_PATH + "/AppleEat.wav"));
		assert(playerDeathSoundBuffer.loadFromFile(RESOURCES_PATH + "/Death.wav"));
		playerDeathSound.setBuffer(playerDeathSoundBuffer);
		appleEatenSound.setBuffer(appleEatenSoundBuffer);
		
		PushGameState(GameState::MainMenu, GameState::None);
		InitRecordTablesData();
	}

	Game::~Game()
	{
		while (!gameStateStack.empty())
		{
			GameStateBase* gameState = gameStateStack.back();
			gameState->End();
			delete gameState;
			gameStateStack.pop_back();
		}
	}

	void Game::Update(const float deltaTime)
	{
		GetCurrentGameState()->Update(deltaTime);
		UpdateGameState();
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (GetCurrentGameState()->GetGameState() == GameState::ReturnToMenuDialog || GetCurrentGameState()->GetGameState() == GameState::Overed)
		{
			(*(gameStateStack.end() - 2))->Draw(window);
		}
		GetCurrentGameState()->Draw(window);
	}

	void Game::setCurrentGameMode(GameModes gameMode)
	{
		currentGameMode = gameMode;
	}

	bool Game::IsGameShuttingDown() const
	{
		return isShuttingDown;
	}

	void Game::Shutdown()
	{
		isShuttingDown = true;
	}

	void Game::AddGameStateSwitchIfQueueEmpty(StateMachineSwitch machineSwitch)
	{
		if (gameStateSwitchQueue.empty())
		{
			gameStateSwitchQueue.push(machineSwitch);
		}
	}

	void Game::SetGameWinnedState(bool currentGameWinned)
	{
		isGameWinned = currentGameWinned;
	}

	void Game::SetGameApplesEaten(int applesEaten)
	{
		numEatenApples = applesEaten;
		recordTableData[currentGameMode][PLAYER_NAME] = std::max(recordTableData[currentGameMode][PLAYER_NAME], numEatenApples);
	}

	int Game::GetGameApplesEaten() const
	{
		return numEatenApples;
	}

	bool Game::GetIsGameWined() const
	{
		return isGameWinned;
	}

	GameModes Game::GetCurrentGameMode() const
	{
		return currentGameMode;
	}

	GameStateBase* Game::GetCurrentGameState()
	{
		return gameStateStack.back();
	}

	void Game::InitRecordTablesData()
	{
		recordTableData.reserve(GAME_MODES_COUNT);
		// Setup input stream for reading player names for record table
		std::ifstream playerNamesInputStream(RESOURCES_PATH + "/recordTableNicknames.txt");
		std::vector<std::string> initialPlayerNames;
		std::string currentPlayerName;

		recordTableData.reserve(GAME_MODES_COUNT);

		while (std::getline(playerNamesInputStream, currentPlayerName))
		{
			initialPlayerNames.push_back(currentPlayerName);
		}

		for (int i = 0; i < GAME_MODES_COUNT; ++i)
		{
			std::unordered_map<std::string, int> currentTable;
			for (int j = 0; j < RECORDS_TABLE_SIZE - 1; ++j)
			{
				int k;
				do
				{
					k = GetRandomIntInRange(0, (int) initialPlayerNames.size() - 1);
				} while (currentTable.contains(initialPlayerNames[k]));
				currentTable.emplace(initialPlayerNames[k], GetRandomIntInRange(0, 
					(i & GameOptions::InfiniteApples) ? (int) (MAX_APPLES * RECORDS_TABLE_MAX_COEFFICIENT) : finiteApplesCount));
			}
			currentTable.emplace(PLAYER_NAME, 0);
			recordTableData.emplace((GameModes)i, currentTable);
		}
		playerNamesInputStream.close();
	}

	void Game::PushGameState(GameState newState, GameState previousState)
	{
		GameStateBase* gameState = nullptr;

		switch (newState)
		{
		case GameState::MainMenu:
		{
			gameState = new MainMenuState(this);
			break;
		}
		case GameState::Starting:
		{
			gameState = new GameStartingState(this);
			break;
		}
		case GameState::Playing:
		{
			gameState = new GamePlayingState(this, finiteApplesCount, &appleEatenSound, &playerDeathSound);
			break;
		}
		case GameState::Overed:
		{
			gameState = new GameOveredState(this);
			break;
		}
		case GameState::RecordTable:
		{
			bool fromMenu = previousState == GameState::MainMenu;
			gameState = new GameRecordsTableState(this, recordTableData, currentGameMode, fromMenu);
			break;
		}
		case GameState::ReturnToMenuDialog:
		{
			gameState = new ReturnToMenuDialogState(this);
			break;
		}
		}

		gameStateStack.push_back(gameState);
		gameState->Start();
	}

	void Game::PopGameState()
	{
		if (!gameStateStack.empty())
		{
			GameStateBase * currentGameState = gameStateStack.back();
			currentGameState->End();
			delete currentGameState;
			gameStateStack.pop_back();
		}
	}
	
	void Game::UpdateGameState()
	{
		if (!gameStateSwitchQueue.empty())
		{
			StateMachineSwitch currentSwitch = gameStateSwitchQueue.front();
			gameStateSwitchQueue.pop();
			GameState previousGameState = GetCurrentGameState()->GetGameState();
			switch (currentSwitch.first)
			{
			case GameStateChangeType::Pop:
			{
				PopGameState();
				break;
			}
			case GameStateChangeType::Switch:
			{
				PopGameState();
				PushGameState(currentSwitch.second, previousGameState);
				break;
			}
			case GameStateChangeType::Push:
			{
				PushGameState(currentSwitch.second, previousGameState);
				break;
			}
			case GameStateChangeType::ClearStackAndPush:
			{
				while (!gameStateStack.empty())
				{
					PopGameState();
				}
				PushGameState(currentSwitch.second, previousGameState);
				break;
			}
			}
		}
	}
}