#include "Game.h"
#include <assert.h>
#include <fstream>
#include <list>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "RecordTable.h"


namespace ApplesGame
{
	void Game::InitGamePlayingState()
	{
		// Init player
		player.SetPosition(Position2D{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		player.SetSpeed(INITIAL_SPEED);
		player.SetDirection(PlayerDirection::Right);
		// Init apples and apples collider grid
		appleCollderGrid.Clear();
		apples.InitApples(gameMode & GameOptions::InfiniteApples ? GetRandomIntInRange(MIN_APPLES, MAX_APPLES) : finiteApplesCount, appleTexture);
		for (int i = 0; i < apples.GetCount(); ++i)
		{
			appleCollderGrid.InsertApple(apples[i], i);
		}
		// Init rocks	
		for (auto& rock : rocks)
		{
			while (rock.TryToSetRockPosition(noRocksRectangle, GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT)));
		}
		numEatenApples = 0;
		gameStateTimer = 0;
	}

	void Game::Init()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));
		assert(playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));
		assert(appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png"));
		assert(rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png"));
		assert(appleEatenSoundBuffer.loadFromFile(RESOURCES_PATH + "/AppleEat.wav"));
		assert(playerDeathSoundBuffer.loadFromFile(RESOURCES_PATH + "/Death.wav"));

		//Get apples count for finite apple game modes
		finiteApplesCount = GetRandomIntInRange(MIN_APPLES, MAX_APPLES);

		//Set size for apple collider grid
		appleCollderGrid.SetGridSize(APPLES_COLLIDER_GRID_HEIGHT, APPLES_COLLIDER_GRID_WIDTH);

		// Setup input stream for reading player names for record table
		std::ifstream playerNamesInputStream(RESOURCES_PATH + "/recordTableNicknames.txt");

		gameUI.Init(font, playerNamesInputStream, finiteApplesCount);

		playerNamesInputStream.close();

		playerDeathSound.setBuffer(playerDeathSoundBuffer);
		appleEatenSound.setBuffer(appleEatenSoundBuffer);
		windowRectangle = Rectangle{ {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, {SCREEN_WIDTH, SCREEN_HEIGHT} };
		noRocksRectangle = Rectangle{ {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, {PLAYER_SIZE * NO_ROCKS_ZONE, PLAYER_SIZE * NO_ROCKS_ZONE} };

		player.Init(playerTexture);

		rocks.reserve(NUM_ROCKS);
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			rocks.push_back(Rock());
			rocks[i].InitRock(rockTexture);
		}

		PushGameState(GameState::Starting);
	}

	void Game::InitGameOveredState()
	{		
		if (!gameWinned)
		{
			playerDeathSound.play();
		}
		gameStateTimer = 0.f;
		gameUI.UpdateStateChanged(GetCurrentGameState(), gameMode, numEatenApples, gameWinned);
	}

	void Game::InitGameRecordTableState()
	{		
		gameStateTimer = 0.f;
		gameUI.UpdateStateChanged(GetCurrentGameState(), gameMode, numEatenApples, gameWinned);
	}

	void Game::Update(const float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			SwitchGameState(GameState::Starting);
		}
		switch (GetCurrentGameState())
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

	void Game::UpdateGamePlayingState(const float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.SetDirection(PlayerDirection::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player.SetDirection(PlayerDirection::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.SetDirection(PlayerDirection::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player.SetDirection(PlayerDirection::Down);
		}

		player.UpdatePosition(deltaTime);

		//apple collision check
		std::list<int> nearestApplesIDList = appleCollderGrid.GetNearestAppleIDsList(player);
		for (auto appleID = nearestApplesIDList.begin(); appleID != nearestApplesIDList.end(); ++appleID)
		{
			if (DoShapesCollide(apples[*appleID].GetCollider(), player.GetCollider()) && !apples.IsAppleEaten(*appleID))
			{
				appleCollderGrid.EraseApple(apples[*appleID], *appleID);
				++numEatenApples;
				appleEatenSound.play();
				if (gameMode & GameOptions::WithAcceleration)
				{
					player.SetSpeed(player.GetSpeed() + ACCELERATION);
				}
				if (gameMode & GameOptions::InfiniteApples)
				{
					apples[*appleID].SetPosition(GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
					appleCollderGrid.InsertApple(apples[*appleID], *appleID);
				}
				else 
				{
					apples.SetAppleEaten(*appleID);
					if (numEatenApples == apples.ApplesCount())
					{
						gameWinned = true;
						SwitchGameState(GameState::GameOvered);
					}
				}
			}
		}

		//border collision check
		if (IsNotCompletelyInRectangle(player.GetCollider(), windowRectangle))
		{
			SwitchGameState(GameState::GameOvered);
		}

		//rocks collision check
		for (auto& rock : rocks)
		{
			if (DoShapesCollide(player.GetCollider(), rock.getCollider()))
			{
				SwitchGameState(GameState::GameOvered);
			}
		}		
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
		if (GetCurrentGameState() != GameState::Starting)
		{
			player.Draw(window);
			apples.DrawApples(window);
			for (auto& rock : rocks)
			{
				rock.Draw(window);
			}
		}
		gameUI.Draw(window, GetCurrentGameState(), gameMode);
	}

	void Game::ShutdownGame()
	{

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
		gameUI.UpdateStateChanged(GetCurrentGameState(), gameMode, numEatenApples, gameWinned);
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
			gameMode = GameModes::InfiniteApplesWithAcceleartion;
			SwitchGameState(GameState::Playing);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			gameMode = GameModes::InfinteApplesWithoutAcceleration;
			SwitchGameState(GameState::Playing);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
		{
			gameMode = GameModes::FiniteApllesWithAcceleration;
			SwitchGameState(GameState::Playing);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			gameMode = GameModes::FiniteApplesWithoutAcceleration;
			SwitchGameState(GameState::Playing);
		}
		
	}

	void Game::EndGameStartingState()
	{

	}	
}