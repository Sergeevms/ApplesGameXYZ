#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	enum class GameState
	{
		None = 0,
		Starting,
		Playing,
		GameOvered,
		RecordTable,
		EscapeDialog,
		ShuttingDown
	};

	class GameStateBase
	{
		GameState gameState;
	public:
		GameStateBase(GameState newGameState) : gameState{ newGameState } {};
		GameState GetGameState() const;
		virtual void Start() = 0;
		virtual void Update(const float deltaTime) = 0;
		virtual void End() = 0;
		virtual void Draw(sf::RenderWindow& window) = 0;
	};
}
