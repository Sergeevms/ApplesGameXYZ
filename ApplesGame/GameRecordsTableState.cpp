#include <assert.h>
#include <SFML/Graphics.hpp>
#include "GameRecordsTableState.h"
#include "Utility.h"

namespace ApplesGame
{
	GameRecordsTableState::GameRecordsTableState(Game* currentGame, std::unordered_map<GameModes, std::unordered_map<std::string, int>>& recordTableData,
		GameModes currentGameMode,	bool fromMenu) 
		: selectedMode(currentGameMode), executedFromMenu(fromMenu), game(currentGame)
	{
		assert(textFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Black.ttf"));
		stateUI.Init(textFont, recordTableData, fromMenu);
	}

	void GameRecordsTableState::Update(const float deltaTime)
	{
		stateTimer += deltaTime;
		if (executedFromMenu == false)
		{
			if (stateTimer >= RECORD_TABLE_RESTART_TIME)
			{
				game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Switch, GameState::MainMenu });				
			}
			if (KeyPressed <sf::Keyboard::Escape>())
			{
				game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Push, GameState::ReturnToMenuDialog });
			}
		}
		else
		{
			if (KeyPressed <sf::Keyboard::Tab>() || KeyPressed <sf::Keyboard::Right>())
			{
				selectedMode = GameModes((selectedMode + 1) % GAME_MODES_COUNT);
			}
			if (KeyPressed <sf::Keyboard::Left>())
			{
				selectedMode = GameModes((selectedMode - 1 + GAME_MODES_COUNT) % GAME_MODES_COUNT);
			}
			if (KeyPressed <sf::Keyboard::Escape>())
			{
				game->AddGameStateSwitchIfQueueEmpty(StateMachineSwitch{ GameStateChangeType::Pop, GameState::None });
			}
		}
	}

	void GameRecordsTableState::Draw(sf::RenderWindow& window)
	{
		stateUI.Draw(window, selectedMode, RECORD_TABLE_RESTART_TIME - stateTimer);
	}
}