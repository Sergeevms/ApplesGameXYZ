#include <assert.h>
#include <SFML/Graphics.hpp>
#include "ReturnToMenuDialogState.h"
#include "Constants.h"
#include "Utility.h"
#include "Game.h"

namespace ApplesGame
{
	ReturnToMenuDialogState::ReturnToMenuDialogState(Game* currentGame) : game(currentGame)
	{
		assert(textFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Black.ttf"));
		stateUI.Init(textFont);
	}

	void ReturnToMenuDialogState::Update(const float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::ClearStackAndPush, GameState::MainMenu });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) || KeyPressed<sf::Keyboard::Escape>())
		{
			game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Pop, GameState::None });
		}		
	}
	void ReturnToMenuDialogState::Draw(sf::RenderWindow& window)
	{
		stateUI.Draw(window);
	}
}