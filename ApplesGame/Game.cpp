#include "Game.h"
#include <assert.h>
#include <fstream>
#include <list>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "RecordTable.h"
#include "Utility.h"


namespace ApplesGame
{
	void Game::Init()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));

		//Get apples count for finite apple game modes
		finiteApplesCount = GetRandomIntInRange(MIN_APPLES, MAX_APPLES);		

		// Setup input stream for reading player names for record table
		std::ifstream playerNamesInputStream(RESOURCES_PATH + "/recordTableNicknames.txt");

		gameUI.Start(font, playerNamesInputStream, finiteApplesCount);

		playerNamesInputStream.close();		

		PushGameState(GameState::Starting);
	}

	void Game::InitGameOveredState()
	{		
		if (!isGameWinned)
		{
			playerDeathSound.play();
		}
		gameStateTimer = 0.f;
		gameUI.UpdateStateChanged(GetCurrentGameState(), currentGameMode, numEatenApples, isGameWinned);
	}

	void Game::InitGameRecordTableState()
	{		
		gameStateTimer = 0.f;
		gameUI.UpdateStateChanged(GetCurrentGameState(), currentGameMode, numEatenApples, isGameWinned);
	}

	void Game::Update(const float deltaTime)
	{
		GameState currentGameState = GetCurrentGameState();

		if (KeyPressed <sf::Keyboard::Space>())
		{
			SwitchGameState(GameState::Starting);
		}
		if (currentGameState != GameState::EscapeDialog && KeyPressed <sf::Keyboard::Escape>())
		{
			PushGameState(GameState::EscapeDialog);
		}

		switch (currentGameState)
		{
		case GameState::Starting:
		{
			UpdateGameStartingState();
			break;
		}
		case GameState::Playing:
		{
			UpdateGamePlayingState(deltaTime);
			break;
		}
		case GameState::GameOvered:
		{
			UpdateGameOveredState(deltaTime);
		}
		case GameState::RecordTable:
		{
			UpdateGameRecordTableState(deltaTime);
		}
		case GameState::EscapeDialog:
			UpdateGameEscapeDialog();
		default:
			break;
		}
		gameUI.Update(GetCurrentGameState(), numEatenApples, deltaTime);
	}

	void Game::UpdateGameRecordTableState(const float deltaTime)
	{
		gameStateTimer += deltaTime;
		if (gameStateTimer >= RECORD_TABLE_RESTART_TIME)
		{
			SwitchGameState(GameState::Starting);
		}
	}

	void Game::EndGameRecordTableState()
	{

	}

	void Game::InitGameEscapeDialog()
	{

	}

	void Game::UpdateGameEscapeDialog()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			PushGameState(GameState::ShuttingDown);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) || KeyPressed<sf::Keyboard::Escape>())
		{
			PopGameState();
		}		
	}

	void Game::EndGameEscapeDialog()
	{

	}

	void Game::UpdateGamePlayingState(const float deltaTime)
	{
				
	}

	void Game::EndGamePlayingState()
	{

	}

	void Game::UpdateGameOveredState(const float deltaTime)
	{
		gameStateTimer += deltaTime;
		if (gameStateTimer >= BEFORE_SHOWING_RECORD_TABLE_TIME)
		{
			SwitchGameState(GameState::RecordTable);
		}
	}

	void Game::EndGameOveredState()
	{

	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (GetCurrentGameState() == GameState::Playing)
		{
			player.Draw(window);
			apples.DrawApples(window);
			for (auto& rock : rocks)
			{
				rock.Draw(window);
			}
		}
		gameUI.Draw(window, GetCurrentGameState(), currentGameMode);
	}

	bool Game::IsGameShuttingDown()
	{
		if (GetCurrentGameState() == GameState::ShuttingDown)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Game::TryToAddGameStateSwitchToQueue(StateMachineSwitch&& machineSwitch)
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

	void Game::SetCurrentGameApplesEaten(int applesEaten)
	{
		numEatenApples = applesEaten;
	}

	GameState Game::GetCurrentGameState()
	{
		return gameStateStack.back();
	}

	void Game::PushGameState(GameState state)
	{
		GameState oldState = GameState::None;

		if (gameStateStack.size() > 0)
		{
			oldState = gameStateStack.back();
		}

		SwitchGameStateInternal(oldState, state);
		gameStateStack.push_back(state);
	}

	void Game::PopGameState()
	{
		GameState oldState = GameState::None;
		GameState state = GameState::None;
		if (gameStateStack.size() > 0)
		{
			oldState = gameStateStack.back();			
		}
		gameStateStack.pop_back();

		if (gameStateStack.size() > 0)
		{
			state = gameStateStack.back();
		}		
		SwitchGameStateInternal(oldState, state);
	}

	void Game::SwitchGameState(GameState newState)
	{
		if (gameStateStack.size() > 0)
		{
			GameState oldState = gameStateStack.back();
			gameStateStack.pop_back();
			gameStateStack.push_back(newState);
			SwitchGameStateInternal(oldState, newState);
		}
		else
		{
			PushGameState(newState);
		}
		gameUI.UpdateStateChanged(GetCurrentGameState(), currentGameMode, numEatenApples, isGameWinned);
	}

	void Game::SwitchGameStateInternal(GameState oldState, GameState newState)
	{
		switch (oldState)
		{
		case GameState::Starting:
		{
			EndGameStartingState();
			break;
		}
		case GameState::Playing:
		{
			EndGamePlayingState();
			break;
		}
		case GameState::GameOvered:
		{
			EndGameOveredState();
			break;
		}
		case GameState::RecordTable:
		{
			EndGameRecordTableState();
			break;
		}
		case GameState::EscapeDialog:
			EndGameEscapeDialog();
			return;
			break;
		}

		switch (newState)
		{
		case GameState::Starting:
		{
			InitGameStartingState();
			break;
		}
		case GameState::Playing:
		{
			InitGamePlayingState();
			break;
		}
		case GameState::GameOvered:
		{
			InitGameOveredState();
			break;
		}
		case GameState::RecordTable:
		{
			InitGameRecordTableState();
			break;
		}		
		}
	}

	void Game::InitGameStartingState()
	{

	}

	void Game::UpdateGameStartingState()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			currentGameMode = GameModes::InfiniteApplesWithAcceleartion;
			SwitchGameState(GameState::Playing);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			currentGameMode = GameModes::InfinteApplesWithoutAcceleration;
			SwitchGameState(GameState::Playing);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
		{
			currentGameMode = GameModes::FiniteApllesWithAcceleration;
			SwitchGameState(GameState::Playing);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			currentGameMode = GameModes::FiniteApplesWithoutAcceleration;
			SwitchGameState(GameState::Playing);
		}
		
	}

	void Game::EndGameStartingState()
	{

	}	
}