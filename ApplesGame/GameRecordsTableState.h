#pragma once
#include "GameStateBase.h"
#include "GameRecordsTableUI.h"

namespace ApplesGame
{
	class Game;
	enum GameModes;

	class GameRecordsTableState :
		public GameStateBase
	{
		bool executedFromMenu{ true };
		GameModes selectedMode{ GameModes::FiniteApplesWithoutAcceleration };
		float stateTimer = 0.f;
		Game* game;
		sf::Font textFont;
		GameRecordsTableUI stateUI;
	public:
		GameRecordsTableState(Game* currentGame, std::unordered_map<GameModes, std::unordered_map<std::string, int>>& recordTableData, 
			GameModes currentGameMode,
			bool fromMenu);
		GameState GetGameState() const override { return GameState::RecordTable; };
		void Update(const float deltaTime) override;
		void Draw(sf::RenderWindow& window) override;
		~GameRecordsTableState() = default;
	};
}