#include "Apple.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
	void InitApple(Apple& apple, const Game& game)
	{
		apple.applePosition = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		apple.sprite.setTexture(game.appleTexture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteOrigin(apple.sprite, 0.5, 0.5);
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition({ apple.applePosition.x, apple.applePosition.y });
		window.draw(apple.sprite);
	}

	void SetApplePosition(Apple& apple, const Position2D newPosition)
	{
		apple.applePosition = newPosition;
	}

	Position2D GetPosition(const Apple& apple)
	{
		return apple.applePosition;
	}
		
	Circle GetAppleCollider(const Apple& apple)
	{
		return Circle{ apple.applePosition, APPLE_SIZE / 2.f };
	}	
}