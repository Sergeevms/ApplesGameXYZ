#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	Position2D GetRandomPositionInScreen(const float screenWidth, const float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
		return result;
	}

	int GetRandomIntInRange(const int min, const int max)
	{
		return min + rand() % (max + 1 - min);
	}

	bool DoShapesCollide(const Circle& Circle1, const Circle& Circle2)
	{
		const float squareDistance = (Circle1.position.x - Circle2.position.x) * (Circle1.position.x - Circle2.position.x) +
			(Circle1.position.y - Circle2.position.y) * (Circle1.position.y - Circle2.position.y);
		const float squareRadiusSum = (Circle1.radius + Circle2.radius) * (Circle1.radius + Circle2.radius);
		return squareDistance <= squareRadiusSum;
	}

	bool DoShapesCollide(const Rectangle& Rectangle1, const Rectangle& Rectangle2)
	{
		const float dx = fabs(Rectangle1.position.x - Rectangle2.position.x);
		const float dy = fabs(Rectangle1.position.y - Rectangle2.position.y);
		return (dx <= (Rectangle1.size.x + Rectangle2.size.x) / 2.f &&
			dy <= (Rectangle1.size.y + Rectangle2.size.y) / 2.f);
	}

	bool DoShapesCollide(const Circle& circle, const Rectangle& rectangle)
	{
		const float dx = fabs(circle.position.x - rectangle.position.x);
		const float dy = fabs(circle.position.y - rectangle.position.y);
		if (dx > (rectangle.size.x / 2.f + circle.radius))
			return false;
		if (dy > (rectangle.size.y / 2.f + circle.radius))
			return false;
		if (dx <= rectangle.size.x / 2.f)
			return true;
		if (dy <= rectangle.size.y / 2.f)
			return true;
		const float squareDistance = (dx - rectangle.size.x / 2.f) * (dx - rectangle.size.x / 2.f) +
			(dy - rectangle.size.y / 2.f) * (dy - rectangle.size.y / 2.f);
		return squareDistance <= circle.radius * circle.radius;
	}

	bool IsNotCompletelyInRectangle(const Circle& circle, const Rectangle& rectangle)
	{
		return (circle.position.x - circle.radius <= rectangle.position.x - rectangle.size.x / 2.f) ||
			(circle.position.x + circle.radius >= rectangle.position.x + rectangle.size.x / 2.f) ||
			(circle.position.y - circle.radius <= rectangle.position.y - rectangle.size.y / 2.f) ||
			(circle.position.y + circle.radius >= rectangle.position.y + rectangle.size.y / 2.f);
	}

	void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight)
	{
		const sf::FloatRect spriteRect = sprite.getLocalBounds();
		const sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}
}