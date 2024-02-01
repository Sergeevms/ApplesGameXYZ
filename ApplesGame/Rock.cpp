#include "Rock.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
	void Rock::InitRock(const sf::Texture& rockTexture)
	{
		sprite.setTexture(rockTexture);
		SetSpriteSize(sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteOrigin(sprite, 0.5f, 0.5f);
	}

	bool Rock::TryToSetRockPosition(const Rectangle& noRocksRectangle, const Position2D newPosition)
	{
		position.x = newPosition.x;
		position.y = newPosition.y;
		return DoShapesCollide(noRocksRectangle, getCollider());
	}

	void Rock::Draw(sf::RenderWindow& window)
	{
		sprite.setPosition({ position.x, position.y });
		window.draw(sprite);
	}

	Rectangle Rock::getCollider()
	{
		return Rectangle{ position, Vector2D{ROCK_SIZE, ROCK_SIZE} };
	}
}