#include <assert.h>
#include "GamePlayingState.h"
#include "Constants.h"
#include "Game.h"

ApplesGame::GamePlayingState::GamePlayingState(Game* currentGame, int finiteApplesCount) : GameStateBase(GameState::Playing), game(currentGame)
{
	assert(playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));
	assert(appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png"));
	assert(rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png"));
	assert(appleEatenSoundBuffer.loadFromFile(RESOURCES_PATH + "/AppleEat.wav"));
	assert(playerDeathSoundBuffer.loadFromFile(RESOURCES_PATH + "/Death.wav"));

	//Set size for apple collider grid
	appleCollderGrid.SetGridSize(APPLES_COLLIDER_GRID_HEIGHT, APPLES_COLLIDER_GRID_WIDTH);

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
	gameStateTimer = 0;
}

void ApplesGame::GamePlayingState ::Start()
{
}

void ApplesGame::GamePlayingState ::Update(const float deltaTime)
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
					game->SetGameWinnedState(true);
					game->TryToAddGameStateSwitchToQueue(StateMachineSwitch{ GameStateChangeType::Switch, GameState::GameOvered });
				}
			}
		}
	}

	//border collision check
	if (IsNotCompletelyInRectangle(player.GetCollider(), windowRectangle))
	{
		game->TryToAddGameStateSwitchToQueue(StateMachineSwitch{ GameStateChangeType::Switch, GameState::GameOvered });
	}

	//rocks collision check
	for (auto& rock : rocks)
	{
		if (DoShapesCollide(player.GetCollider(), rock.getCollider()))
		{
			game->TryToAddGameStateSwitchToQueue(StateMachineSwitch{ GameStateChangeType::Switch, GameState::GameOvered });
		}
	}
}

void ApplesGame::GamePlayingState::End()
{

}
