#include <assert.h>
#include <SFML/Graphics.hpp>

#include "MainMenuState.h"
#include "Constants.h"
#include "Game.h"
#include "Utility.h"

namespace ApplesGame
{

	MainMenu::MainMenu()
	{
		//
#ifdef NDEBUG
		menuFont.loadFromFile(RESOURCES_PATH + "/Fonts/Roboto-Bold.ttf"); 
#else 
		assert(menuFont.loadFromFile(RESOURCES_PATH + "/Fonts/Roboto-Bold.ttf"));
#endif // !NDEBUG

		

		initMenuNode(&root, menuFont, "Apples Game Menu", "");
		initMenuNode(&play, menuFont, "", "Play");
		addChildNode(&root, &play);
		initMenuNode(&options, menuFont, "Game options", "Options");
		addChildNode(&root, &options);
		initMenuNode(&recordsTable, menuFont, "", "Table of records");
		addChildNode(&root, &recordsTable);
		initMenuNode(&exit, menuFont, "Exit game?", "Exit", Orientation::Horizontal, Alignment::Middle, 50.f);
		addChildNode(&root, &exit);

		initMenuNode(&infiniteAppleOption, menuFont, "", "Infinite apples: off");
		addChildNode(&options, &infiniteAppleOption);
		initMenuNode(&accelerationOption, menuFont, "", "Acceleration: off");
		addChildNode(&options, &accelerationOption);

		initMenuNode(&yesOnExit, menuFont, "", "Yes");
		addChildNode(&exit, &yesOnExit);
		initMenuNode(&noOnExit, menuFont, "", "No");
		addChildNode(&exit, &noOnExit);

		currentNode = &root;
		currentNode->selectedChild = *(currentNode->childNodes.begin());
		setStyleActive(currentNode->selectedChild);
	}

	void MainMenu::UpdateOptionsText(GameModes gameMode)
	{
		std::string optionString;

		optionString.assign("Infinite apples: ");
		if (gameMode & GameOptions::InfiniteApples)
		{
			optionString.append("Yes");
		}
		else
		{
			optionString.append("No");
		}
		infiniteAppleOption.text.setString(optionString);

		optionString.assign("Acceleration apples: ");
		if (gameMode & GameOptions::WithAcceleration)
		{
			optionString.append("Yes");
		}
		else
		{
			optionString.append("No");
		}
		accelerationOption.text.setString(optionString);
	}

	MainMenuState::MainMenuState(Game * currentGame) : game(currentGame)
	{
		menu.UpdateOptionsText(game->GetCurrentGameMode());
	}

	void MainMenuState::Update(const float deltaTime)
	{
		if (KeyPressed<sf::Keyboard::Enter>())
		{
			if (!menu.ExpandSelected())
			{
				MenuNode* selectedRow = menu.currentNode->selectedChild;
				if (selectedRow == &(menu.play))
				{
					game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Switch, GameState::Playing });
				}
				else if (selectedRow == &(menu.recordsTable))
				{
					game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Push, GameState::RecordTable });
				}
				else if (selectedRow == &(menu.yesOnExit))
				{
					game->Shutdown();
				}
				else if (selectedRow == &(menu.noOnExit))
				{
					menu.ReturnToPrevios();
				} 
				else if (selectedRow == &(menu.accelerationOption))
				{
					GameModes newMode = GameModes(game->GetCurrentGameMode() ^ GameOptions::WithAcceleration);
					game->setCurrentGameMode(newMode);
					menu.UpdateOptionsText(newMode);
				}
				else if (selectedRow == &(menu.infiniteAppleOption))
				{
					GameModes newMode = GameModes(game->GetCurrentGameMode() ^ GameOptions::InfiniteApples);
					game->setCurrentGameMode(newMode);
					menu.UpdateOptionsText(newMode);
				}
			}
		}

		Orientation orientation = menu.currentNode->subMenuOrientation;
		if ( (orientation == Orientation::Vertical && (KeyPressed<sf::Keyboard::Up>() || KeyPressed<sf::Keyboard::W>() ))
			|| (orientation == Orientation::Horizontal && (KeyPressed<sf::Keyboard::Left>() || KeyPressed<sf::Keyboard::A>() )) )
		{
			selectPreviosChildNode(menu.currentNode);
		}
		else if ( (orientation == Orientation::Vertical && (KeyPressed<sf::Keyboard::Down>() || KeyPressed<sf::Keyboard::S>() ))
			|| (orientation == Orientation::Horizontal && (KeyPressed<sf::Keyboard::Right>() || KeyPressed<sf::Keyboard::D>() )) )
		{
			selectNextChildNode(menu.currentNode);
		}

		if (KeyPressed <sf::Keyboard::Escape>())
		{
			menu.ReturnToPrevios();
		}
	}

	void MainMenuState::Draw(sf::RenderWindow& window)
	{
		menu.Draw(window);
	}
}