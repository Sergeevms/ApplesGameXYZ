#include "Game.h"
#include <assert.h>
#include "Constants.h"
#include "Math.h"
#include "Player.h"

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
		game.timeSinceGameOvered = 0;
	}

	void InitGame(Game& game)
	{
		assert(game.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png"));
		assert(game.appleEatenSoundBuffer.loadFromFile(RESOURCES_PATH + "/AppleEat.wav"));
		assert(game.playerDeathSoundBuffer.loadFromFile(RESOURCES_PATH + "/Death.wav"));

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
		SetGameOveredTypeStateUI(game.uiState, game.gameState);
		if (!(game.gameState & Game::GameState::IsGameWinned))
		{
			game.playerDeathSound.play();
		}
		game.timeSinceGameOvered = 0.f;
		game.gameState |= Game::GameState::IsGameOvered;
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
		else if (!(game.gameState & Game::GameState::IsGameOvered))
		{
			UpdateGamePlayingState(game, deltaTime);
		}
		else
		{
			UpdateGameOveredState(game, deltaTime);
		}
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
		game.timeSinceGameOvered += deltaTime;
		if (game.timeSinceGameOvered >= RESTART_TIME)
		{
			StartGameStartingState(game);
		}
		UpdateGameOveredStateUI(game.uiState, game);
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
		game.gameState |= Game::GameState::IsGameRestarting;
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