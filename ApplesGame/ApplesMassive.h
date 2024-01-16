#pragma once
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
		int applesCount;
		uint8_t* isAppleEaten;
		Apple* apples;
	public:
		ApplesMassive() :applesCount{ 0 }, apples{ nullptr }, isAppleEaten{ nullptr } {};
		~ApplesMassive();
		void InitApples(const int newApplesCount, const Game& game);
		void DrawApples(sf::RenderWindow& window);
		bool IsAppleEaten(int i);
		void SetAppleEaten(int i);
		int GetCount();
		Apple* Begin();
		Apple* End();
		int ApplesCount() const;
		Apple& operator[](int i);
	};
}