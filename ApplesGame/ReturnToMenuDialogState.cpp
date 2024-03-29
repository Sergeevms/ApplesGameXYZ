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
		background.setFillColor(sf::Color(0, 0, 0, 128));
		background.setPosition(0.f, 0.f);
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	}

	void ReturnToMenuDialogState::Update(const float deltaTime)
	{
		if (KeyPressed<sf::Keyboard::Enter>())
		{
			if (menu.currentNode->selectedChild == &(menu.continueGame))
			{
				game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Pop, GameState::None });
			}
			else if (menu.currentNode->selectedChild == &(menu.toMainMenu))
			{
				game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::ClearStackAndPush, GameState::MainMenu });
			}
		}
		else if (KeyPressed<sf::Keyboard::Escape>())
		{
			game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Pop, GameState::None });
		}

		Orientation orientation = menu.currentNode->subMenuOrientation;
		if ((orientation == Orientation::Vertical && (KeyPressed<sf::Keyboard::Up>() || KeyPressed<sf::Keyboard::W>()))
			|| (orientation == Orientation::Horizontal && (KeyPressed<sf::Keyboard::Left>() || KeyPressed<sf::Keyboard::A>())))
		{
			selectPreviosChildNode(menu.currentNode);
		}
		else if ((orientation == Orientation::Vertical && (KeyPressed<sf::Keyboard::Down>() || KeyPressed<sf::Keyboard::S>()))
			|| (orientation == Orientation::Horizontal && (KeyPressed<sf::Keyboard::Right>() || KeyPressed<sf::Keyboard::D>())))
		{
			selectNextChildNode(menu.currentNode);
		}
	}

	void ReturnToMenuDialogState::Draw(sf::RenderWindow& window)
	{
		window.draw(background);
		menu.Draw(window);
	}

	PauseMenu::PauseMenu()
	{
#ifndef NDEBUG
		assert(menuFont.loadFromFile(RESOURCES_PATH + "/Fonts/Roboto-Bold.ttf"));
#else
		menuFont.loadFromFile(RESOURCES_PATH + "/Fonts/Roboto-Bold.ttf");
#endif // !NDEBUG

		

		initMenuNode(&root, menuFont, "PAUSE", "", Orientation::Horizontal, Alignment::Middle, 50.f);
		initMenuNode(&continueGame, menuFont, "", "Continue");
		addChildNode(&root, &continueGame);
		initMenuNode(&toMainMenu, menuFont, "", "To main menu");
		addChildNode(&root, &toMainMenu);

		currentNode = &root;
		currentNode->selectedChild = *(currentNode->childNodes.begin());
		setStyleActive(currentNode->selectedChild);
	}
}