#include "Rock.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
	void InitRock(Rock& rock, const Game& game)
	{
		rock.sprite.setTexture(game.rockTexture);
		SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteOrigin(rock.sprite, 0.5f, 0.5f);
	}

	bool TryToSetRockPosition(Rock& rock, const Rectangle& noRocksRectangle, const Position2D position)
	{
		rock.rockPosition.x = position.x;
		rock.rockPosition.y = position.y;
		return DoShapesCollide(noRocksRectangle, getRockCollider(rock));
	}

	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		rock.sprite.setPosition({ rock.rockPosition.x, rock.rockPosition.y });
		window.draw(rock.sprite);
	}

	Rectangle getRockCollider(const Rock& rock)
	{
		return Rectangle{ rock.rockPosition, Vector2D{ROCK_SIZE, ROCK_SIZE} };
	}
}