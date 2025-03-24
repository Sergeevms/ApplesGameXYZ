#include "Apple.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
	Apple::Apple(const sf::Texture& appleTexture)
	{
		applePosition = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		sprite.setTexture(appleTexture);
		SetSpriteSize(sprite, APPLE_SIZE, APPLE_SIZE);
		SetOriginByRelative(sprite, RelativeOrigin{ 0.5f, 0.5f });
	}

	void Apple::DrawApple(sf::RenderWindow& window)
	{
		sprite.setPosition({ applePosition.x, applePosition.y });
		window.draw(sprite);
	}

	void Apple::SetPosition(const Position2D newPosition)
	{
		applePosition = newPosition;
	}

	const Position2D& Apple::GetPosition() const
	{
		return applePosition;
	}
		
	Circle Apple::GetCollider()
	{
		return Circle{ applePosition, APPLE_SIZE / 2.f };
	}	
}