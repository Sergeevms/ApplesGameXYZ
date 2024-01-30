#include "ApplesMassive.h"
#include "Game.h"

namespace ApplesGame
{
	ApplesMassive::ApplesMassive()
	{
		apples.reserve(MAX_APPLES);
		isAppleEaten.reserve((MAX_APPLES >> appleEatenMassiveBitOffset) + 1);
	}

	void ApplesMassive::InitApples(const int newApplesCount, const sf::Texture& appleTexture)
	{		
		applesCount = newApplesCount;
		for (int i = 0; i < applesCount; ++i)
		{
			apples.push_back(Apple(appleTexture));
		}
		for (int i = 0; i < (newApplesCount >> appleEatenMassiveBitOffset) + 1; ++i)
		{
			isAppleEaten.push_back(0);
		}
	}

	void ApplesMassive::DrawApples(sf::RenderWindow& window)
	{
		for (int i = 0; i < applesCount; ++i)
		{
			if (!(isAppleEaten[(i >> appleEatenMassiveBitOffset)] & (1 << (i & applesEatenMask))))
			{
				apples[i].DrawApple(window);
			}
		}
	}

	bool ApplesMassive::IsAppleEaten(const int i)
	{
		return isAppleEaten[i >> appleEatenMassiveBitOffset] & (1 << (i & applesEatenMask));
	}

	void ApplesMassive::SetAppleEaten(const int i)
	{
		isAppleEaten[i >> appleEatenMassiveBitOffset] |= (1 << (i & applesEatenMask));
	}

	int ApplesMassive::GetCount() const
	{
		return applesCount;
	}

	std::vector<Apple>::iterator ApplesMassive::Begin()
	{
		return apples.begin();
	}

	int ApplesMassive::ApplesCount() const
	{
		return applesCount;
	}

	Apple& ApplesMassive::operator[](int i)
	{
		return apples[i];
	}

	std::vector<Apple>::iterator ApplesMassive::End()
	{
		return apples.end();
	}
}