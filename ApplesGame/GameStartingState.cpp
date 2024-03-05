#include <assert.h>
#include "GameStartingState.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
	GameStartingState::GameStartingState(Game* currentGame) :
		game(currentGame)
	{
		assert(textFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));

		stateUI.Init(textFont);
	}

	void GameStartingState::Update(const float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			game->setCurrentGameMode(GameModes::InfiniteApplesWithAcceleartion);
			game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Switch, GameState::Playing });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			game->setCurrentGameMode(GameModes::InfinteApplesWithoutAcceleration);
			game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Switch, GameState::Playing });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
		{
			game->setCurrentGameMode(GameModes::FiniteApllesWithAcceleration);
			game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Switch, GameState::Playing });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			game->setCurrentGameMode(GameModes::FiniteApplesWithoutAcceleration);
			game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Switch, GameState::Playing });
		}
	}

	void GameStartingState::Draw(sf::RenderWindow& window)
	{
		stateUI.Draw(window);
	}
}