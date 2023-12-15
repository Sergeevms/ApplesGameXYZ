#include "ApplesMassive.h"
#include "Game.h"

namespace ApplesGame
{
	ApplesMassive::~ApplesMassive()
	{
		if (apples)
			delete[] apples;
	}
	void ApplesMassive::InitApples(const int newApplesCount, const Game& game)
	{
		if (apples)
			delete[] apples;
		apples = new Apple[newApplesCount];
		applesCount = newApplesCount;
		for (Apple* apple = apples; apple < apples + applesCount; ++apple)
		{
			InitApple(*apple, game);
		}
	}

	void ApplesMassive::DrawApples(sf::RenderWindow& window)
	{
		for (Apple* apple = apples; apple < apples + applesCount; ++apple)
		{
			if (!apple->appleEaten)
			{
				DrawApple(*apple, window);
			}
		}
	}

	Apple* ApplesMassive::begin()
	{
		return apples;
	}

	int ApplesMassive::ApplesCount() const
	{
		return applesCount;
	}

	Apple* ApplesMassive::end()
	{
		return apples + applesCount;
	}
}