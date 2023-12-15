#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	typedef Vector2D Position2D;

	struct Circle
	{
		Position2D position;
		float radius = 0.f;
	};

	struct Rectangle
	{
		Position2D position;
		Vector2D size;
	};

	Position2D GetRandomPositionInScreen(const float screenWidth, const float screenHeight);
	int GetRandomIntInRange(const int min, const int max);

	bool DoShapesCollide(const Circle& Circle1, const Circle& Circle2);
	bool DoShapesCollide(const Rectangle& Rectangle1, const Rectangle& Rectangle2);
	bool DoShapesCollide(const Circle& Circle, const Rectangle& Rectangle);

	bool IsNotCompletelyInRectangle(const Circle& Circle, const Rectangle& Rectangle);

	void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight);
	void SetSpriteOrigin(sf::Sprite& sprite, const float originX, const float originY);
}