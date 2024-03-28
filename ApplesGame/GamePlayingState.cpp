#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GamePlayingState.h"
#include "Constants.h"
#include "Utility.h"
#include "Game.h"

ApplesGame::GamePlayingState::GamePlayingState(Game* currentGame, int finiteApplesCount, 
	sf::Sound* eatenSound, sf::Sound* deathSound) : game(currentGame), appleEatenSound(eatenSound), playerDeathSound(deathSound)
{
	assert(playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));
	assert(appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png"));
	assert(rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png"));
	assert(textFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));

	currentGameMode = game->GetCurrentGameMode();
	game->SetGameWinnedState(false);

	//Set size for apple collider grid
	appleCollderGrid.SetGridSize(APPLES_COLLIDER_GRID_HEIGHT, APPLES_COLLIDER_GRID_WIDTH);

	windowRectangle = Rectangle{ {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, {SCREEN_WIDTH, SCREEN_HEIGHT} };
	noRocksRectangle = Rectangle{ {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f}, {PLAYER_SIZE * NO_ROCKS_ZONE, PLAYER_SIZE * NO_ROCKS_ZONE} };

	stateUI.Init(textFont);

	player.Init(playerTexture);

	rocks.reserve(NUM_ROCKS);
	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		rocks.push_back(Rock());
		rocks[i].InitRock(rockTexture);
	}

	// Init player
	player.SetPosition(Position2D{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	player.SetSpeed(INITIAL_SPEED);
	player.SetDirection(PlayerDirection::Right);
	// Init apples and apples collider grid
	appleCollderGrid.Clear();
	apples.InitApples(currentGameMode && GameOptions::InfiniteApples ? GetRandomIntInRange(MIN_APPLES, MAX_APPLES) : finiteApplesCount, appleTexture);
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
	stateUI.UpdatePlayerScore(numEatenApples);
	gameStateTimer = 0;
}

void ApplesGame::GamePlayingState ::Update(const float deltaTime)
{
	if (KeyPressed<sf::Keyboard::Escape>())
	{
		game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Push, GameState::ReturnToMenuDialog });
	}
	
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
			stateUI.UpdatePlayerScore(++numEatenApples);
			appleEatenSound->play();
			if (currentGameMode & GameOptions::WithAcceleration)
			{
				player.SetSpeed(player.GetSpeed() + ACCELERATION);
			}
			if (currentGameMode & GameOptions::InfiniteApples)
			{
				apples[*appleID].SetPosition(GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
				appleCollderGrid.InsertApple(apples[*appleID], *appleID);
			}
			else
			{
				apples.SetAppleEaten(*appleID);
				if (numEatenApples == apples.ApplesCount())
				{
					EndGame(true);
				}
			}
		}
	}

	//border collision check
	if (IsNotCompletelyInRectangle(player.GetCollider(), windowRectangle))
	{
		EndGame();
	}

	//rocks collision check
	for (auto& rock : rocks)
	{
		if (DoShapesCollide(player.GetCollider(), rock.GetCollider()))
		{
			EndGame();
		}
	}
}

void ApplesGame::GamePlayingState::Draw(sf::RenderWindow& window)
{
	player.Draw(window);
	apples.DrawApples(window);
	for (auto& rock : rocks)
	{
		rock.Draw(window);
	}
	stateUI.Draw(window);
}

void ApplesGame::GamePlayingState::EndGame(bool gameWinned)
{
	game->SetGameWinnedState(gameWinned);
	game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Push, GameState::Overed });
	game->SetGameApplesEaten(numEatenApples);
	if (!gameWinned)
	{
		playerDeathSound->play();
	}
}