#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"

namespace ApplesGame
{
	class GameLoop
	{
		sf::RenderWindow* window = nullptr;
		Game* game = nullptr;
	public:
		GameLoop();
		~GameLoop();
		void Run();
	};
}

