#include <assert.h>
#include <SFML/Graphics.hpp>
#include "GameOveredState.h"
#include "Constants.h"
#include "Utility.h"
#include "Game.h"

namespace ApplesGame
{

	GameOveredState::GameOveredState(Game* currentGame) :
		game(currentGame)
	{
		assert(textFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Black.ttf"));

		stateUI.Init(textFont, game->GetIsGameWined(), game->GetGameApplesEaten());
	}

	void GameOveredState::Update(const float deltaTime)
	{
		if (KeyPressed<sf::Keyboard::Escape>())
		{
			game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Push, GameState::ReturnToMenuDialog });
		}

		gameStateTimer += deltaTime;
		if (gameStateTimer >= BEFORE_SHOWING_RECORD_TABLE_TIME)
		{
			game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Switch, GameState::RecordTable });
		}
	}

	void GameOveredState::Draw(sf::RenderWindow& window)
	{
		stateUI.Draw(window);
	}
}