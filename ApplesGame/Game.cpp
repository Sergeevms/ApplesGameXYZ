#include "Game.h"
#include <assert.h>
#include <fstream>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "RecordTable.h"


namespace ApplesGame
{
	void StartGamePlayingState(Game& game)
	{
		// Init player
		InitPlayer(game.player, game);
		SetPlayerPosition(game.player, Position2D{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		SetPlayerSpeed(game.player, INITIAL_SPEED);
		SetPlayerDirection(game.player, PlayerDirection::Right);
		// Init apples
		game.apples.InitApples(GetRandomIntInRange(MIN_APPLES, MAX_APPLES), game);
		// Init rocks	
		for (auto& rock : game.rocks)
		{
			while (TryToSetRockPosition(rock, game.noRocksRectangle, GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT)));
		}
		game.numEatenApples = 0;
		game.gameOveredTimer = 0;
	}

	void InitGame(Game& game)
	{
		assert(game.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png"));
		assert(game.appleEatenSoundBuffer.loadFromFile(RESOURCES_PATH + "/AppleEat.wav"));
		assert(game.playerDeathSoundBuffer.loadFromFile(RESOURCES_PATH + "/Death.wav"));

		//Get apples count for finite apple game modes
		game.finiteApplesCount = GetRandomIntInRange(MIN_APPLES, MAX_APPLES);

		// Read player names for record table and initialize record tables for each game mode
		std::ifstream playerNamesInputStream(RESOURCES_PATH + "/recordTableNicknames.txt");
		std::vector<std::string> initialPlayerNames;
		std::string currentPlayerName;
		while (std::getline(playerNamesInputStream, currentPlayerName))
		{
			initialPlayerNames.push_back(currentPlayerName);
		}
		for (int i = 0; i < 4; ++i)
		{
			game.uiState.recordTables.push_back(RecordTable(initialPlayerNames, RECORDS_TABLE_SIZE, 
				Game::GameState::IsInfiniteApples & i ? MAX_APPLES : game.finiteApplesCount, game.font, i));
		}


		InitUI(game.uiState, game.font);
		game.playerDeathSound.setBuffer(game.playerDeathSoundBuffer);
		game.appleEatenSound.setBuffer(game.appleEatenSoundBuffer);
		game.windowRectangle = Rectangle{ {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, {SCREEN_WIDTH, SCREEN_HEIGHT} };
		game.noRocksRectangle = Rectangle{ {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, {PLAYER_SIZE * NO_ROCKS_ZONE, PLAYER_SIZE * NO_ROCKS_ZONE} };

		InitPlayer(game.player, game);
		game.numEatenApples = 0;
		for (auto& rock : game.rocks)
		{
			InitRock(rock, game);
		}
		StartGameStartingState(game);
	}

	void StartGameOveredState(Game& game)
	{
		SetGameOveredTypeStateUI(game.uiState, game);
		if (!(game.gameState & Game::GameState::IsGameWinned))
		{
			game.playerDeathSound.play();
		}
		game.gameOveredTimer = 0.f;
		game.gameState |= Game::GameState::IsGameOvered;
	}

	void StartGameRecordTableState(Game& game)
	{
		game.gameState |= Game::GameState::IsRecordTableShowing;
		game.gameOveredTimer = 0.f;
		UpdatePlayerRecord(game.uiState, game);
	}

	void UpdateGame(Game& game, const float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !(game.gameState & Game::GameState::IsGameRestarting))
		{
			StartGameStartingState(game);
		}
		if (game.gameState & Game::GameState::IsGameRestarting)
		{
			UpdateGameStartingState(game);
		}
		else if (game.gameState & Game::GameState::IsRecordTableShowing)
		{
			UpdateGameRecordTableState(game, deltaTime);
		}
		else if (!(game.gameState & Game::GameState::IsGameOvered))
		{
			UpdateGamePlayingState(game, deltaTime);
		}
		else
		{
			UpdateGameOveredState(game, deltaTime);
		}
	}

	void UpdateGameRecordTableState(Game& game, const float deltaTime)
	{
		game.gameOveredTimer += deltaTime;
		UpdateRecordTableStateUI(game.uiState, game);
	}

	void UpdateGamePlayingState(Game& game, const float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			SetPlayerDirection(game.player, PlayerDirection::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			SetPlayerDirection(game.player, PlayerDirection::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			SetPlayerDirection(game.player, PlayerDirection::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			SetPlayerDirection(game.player, PlayerDirection::Down);
		}

		UpdatePlayerPosition(game.player, deltaTime);

		//apple collision check
		for (int i = 0; i < game.apples.GetCount(); ++i)
		{
			if (DoShapesCollide(GetAppleCollider(game.apples[i]), GetPlayerCollider(game.player)) && !game.apples.IsAppleEaten(i))
			{
				++game.numEatenApples;
				game.appleEatenSound.play();
				if (game.gameState & Game::GameState::IsWithAcceleration)
				{
					SetPlayerSpeed(game.player, GetPlayerSpeed(game.player) + ACCELERATION);
				}
				if (game.gameState & Game::GameState::IsInfiniteApples)
				{
					SetApplePosition(game.apples[i], GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
				}
				else 
				{
					game.apples.SetAppleEaten(i);
					if (game.numEatenApples == game.apples.ApplesCount())
					{
						game.gameState |= Game::GameState::IsGameWinned;
						StartGameOveredState(game);
					}
				}
			}
		}

		//border collision check
		if (IsNotCompletelyInRectangle(GetPlayerCollider(game.player), game.windowRectangle))
		{
			StartGameOveredState(game);
		}

		//rocks collision check
		for (auto& rock : game.rocks)
		{
			if (DoShapesCollide(GetPlayerCollider(game.player), getRockCollider(rock)))
			{
				StartGameOveredState(game);
			}
		}
		UpdateGamePlayingStateUI(game.uiState, game);
	}

	void UpdateGameOveredState(Game& game, const float deltaTime)
	{
		game.gameOveredTimer += deltaTime;
		if (game.gameOveredTimer >= BEFORE_SHOWING_RECORD_TABLE_TIME)
		{
			StartGameRecordTableState(game);
		}
	}

	void DrawGame(sf::RenderWindow& window, Game& game)
	{
		if (!(game.gameState & Game::GameState::IsGameRestarting))
		{
			DrawPlayer(game.player, window);
			game.apples.DrawApples(window);
			for (auto& rock : game.rocks)
			{
				DrawRock(rock, window);
			}
		}
		DrawUI(game.uiState, window, game.gameState);
	}

	void StartGameStartingState(Game& game)
	{
		game.gameState = Game::GameState::IsGameRestarting;
	}

	void UpdateGameStartingState(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			game.gameState = Game::GameState::IsInfiniteApples | Game::GameState::IsWithAcceleration;
			StartGamePlayingState(game);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			game.gameState = Game::GameState::IsInfiniteApples;
			StartGamePlayingState(game);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
		{
			game.gameState = Game::GameState::IsWithAcceleration;
			StartGamePlayingState(game);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			game.gameState = 0;
			StartGamePlayingState(game);
		}
	}
}