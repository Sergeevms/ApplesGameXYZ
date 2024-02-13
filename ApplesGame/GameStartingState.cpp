#include <assert.h>
#include "GameStartingState.h"

namespace ApplesGame
{
	GameStartingState::GameStartingState(Game* currentGame) : GameStateBase(GameState::Starting)
	{
		assert(textFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));

		stateUI.Init(textFont);
	}

	void GameStartingState::Start()
	{

	}

	void GameStartingState::Update()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			game->setCurrentGameMode(GameModes::InfiniteApplesWithAcceleartion);
			game->TryToAddGameStateSwitchToQueue(StateMachineSwitch{ GameStateChangeType::Switch, GameState::Playing });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			game->setCurrentGameMode(GameModes::InfinteApplesWithoutAcceleration);
			game->TryToAddGameStateSwitchToQueue(StateMachineSwitch{ GameStateChangeType::Switch, GameState::Playing });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
		{
			game->setCurrentGameMode(GameModes::FiniteApllesWithAcceleration);
			game->TryToAddGameStateSwitchToQueue(StateMachineSwitch{ GameStateChangeType::Switch, GameState::Playing });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			game->setCurrentGameMode(GameModes::FiniteApplesWithoutAcceleration);
			game->TryToAddGameStateSwitchToQueue(StateMachineSwitch{ GameStateChangeType::Switch, GameState::Playing });
		}
	}

	void GameStartingState::End()
	{

	}

	void GameStartingState::Draw(sf::RenderWindow& window)
	{

	}
}