#pragma once
#include "Apple.h"

namespace ApplesGame
{
	struct Game;

	class ApplesMassive
	{
		int applesCount;
		Apple* apples;
	public:
		ApplesMassive() : apples{ nullptr }, applesCount{ 0 } {};
		~ApplesMassive();
		void InitApples(const int newApplesCount, const Game& game);
		void DrawApples(sf::RenderWindow& window);
		Apple* begin();
		Apple* end();
		int ApplesCount() const;
	};
}