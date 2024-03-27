#pragma once

namespace ApplesGame
{	

	enum class GameState
	{
		None = 0,
		Starting,
		Playing,
		Overed,
		RecordTable,
		ReturnToMenuDialog,
		MainMenu
	};

	class GameStateBase
	{
	public:		
		virtual GameState GetGameState() const = 0;
		virtual void Start() {};
		virtual void Update(const float deltaTime) = 0;
		virtual void End() {};
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual ~GameStateBase() {};
	};
}
