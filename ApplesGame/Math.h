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

	/* Origin position coordinate relative to Left Top corner;
		x, y must be in [0, 1] range; 
		{1.f, 1.f} for bottom right corner, {0.f, 0.f} fo left top,	{0.5f, 0} for middle in x axis, top in y axis, etc.	*/
	struct RelativeOrigin
	{
		float x = 0.f;
		float y = 0.f;
	};

	Position2D GetRandomPositionInScreen(const float screenWidth, const float screenHeight);
	int GetRandomIntInRange(const int min, const int max);

	bool DoShapesCollide(const Circle& Circle1, const Circle& Circle2);
	bool DoShapesCollide(const Rectangle& Rectangle1, const Rectangle& Rectangle2);
	bool DoShapesCollide(const Circle& Circle, const Rectangle& Rectangle);

	bool IsNotCompletelyInRectangle(const Circle& Circle, const Rectangle& Rectangle);

	void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight);

	
	/*Consept for function to set origin by RelativeOrigin*/
	template <typename T>
	concept haveMethodsForRelativeOriginSetGet = requires(T & a, float x)
	{
		{ a.getLocalBounds() }-> std::same_as<sf::FloatRect>;
		a.setOrigin(x, x);
	};

	/*Function to set origin by RelativeOrigin*/
	template<typename T>
	void SetOriginByRelative(T& object, const RelativeOrigin relativeOrigin)
		requires haveMethodsForRelativeOriginSetGet<T>
	{
		const sf::FloatRect objectBoundRect = object.getLocalBounds();
		object.setOrigin(objectBoundRect.width * relativeOrigin.x, objectBoundRect.height * relativeOrigin.y);
	}
}