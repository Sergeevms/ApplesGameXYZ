#include "ApplesMassive.h"
#include "Game.h"

namespace ApplesGame
{
	ApplesMassive::~ApplesMassive()
	{
		if (apples)
			delete[] apples;
		if (isAppleEaten)
			delete[] isAppleEaten;
	}

	void ApplesMassive::InitApples(const int newApplesCount, const Game& game)
	{
		if (apples)
			delete[] apples;
		if (isAppleEaten)
			delete[] isAppleEaten;
		apples = new Apple[newApplesCount];
		isAppleEaten = new uint8_t[(newApplesCount >> appleEatenMassiveBitOffset) + 1]{ 0 };
		applesCount = newApplesCount;
		for (Apple* apple = apples; apple < apples + applesCount; ++apple)
		{
			InitApple(*apple, game);
		}
	}

	void ApplesMassive::DrawApples(sf::RenderWindow& window)
	{
		for (int i = 0; i < applesCount; ++i)
		{
			if (!(isAppleEaten[(i >> appleEatenMassiveBitOffset)] & (1 << (i & applesEatenMask))))
			{
				DrawApple(apples[i], window);
			}
		}
	}

	bool ApplesMassive::IsAppleEaten(int i)
	{
		return isAppleEaten[i >> appleEatenMassiveBitOffset] & (1 << (i & applesEatenMask));
	}

	void ApplesMassive::SetAppleEaten(int i)
	{
		isAppleEaten[i >> appleEatenMassiveBitOffset] |= (1 << (i & applesEatenMask));
	}

	int ApplesMassive::GetCount()
	{
		return applesCount;
	}

	Apple* ApplesMassive::Begin()
	{
		return apples;
	}

	int ApplesMassive::ApplesCount() const
	{
		return applesCount;
	}

	Apple& ApplesMassive::operator[](int i)
	{
		return *(apples + i);
	}

	Apple* ApplesMassive::End()
	{
		return apples + applesCount;
	}
}