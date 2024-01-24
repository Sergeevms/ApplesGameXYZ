#pragma once
#include <vector>

#include "Apple.h"

namespace ApplesGame
{
	struct Game;

	class ApplesMassive
	{
		enum AppleEatenState
		{
			IsEaten = 0,
			IsNotEaten = 1
		};

		const static int appleEatenMassiveBitOffset = 3;
		const static int applesEatenMask = (1 << appleEatenMassiveBitOffset) - 1;
		int applesCount = 0;
		std::vector<uint8_t> isAppleEaten;
		std::vector<Apple> apples;

	public:
		ApplesMassive();
		void InitApples(const int newApplesCount, const Game& game);
		void DrawApples(sf::RenderWindow& window);
		bool IsAppleEaten(const int i);
		void SetAppleEaten(const int i);
		int GetCount() const;
		std::vector<Apple>::iterator Begin();
		std::vector<Apple>::iterator End();
		int ApplesCount() const;
		Apple& operator[](int i);
	};
}