#include "Player.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
	void Player::Init(const sf::Texture& playerTexture)
	{
		sprite.setTexture(playerTexture);
		SetSpriteSize(sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetOriginByRelative(sprite, RelativeOrigin{ 0.5, 0.5 });
	}

	void Player::Draw(sf::RenderWindow& window)
	{
		sprite.setPosition(position.x, position.y);

		if (direction == PlayerDirection::Left)
		{
			SetSpriteSize(sprite, -PLAYER_SIZE, PLAYER_SIZE);
			sprite.setRotation(0.f);
		}
		else
		{
			SetSpriteSize(sprite, PLAYER_SIZE, PLAYER_SIZE);
			sprite.setRotation(-90.f * (float)direction);
		}
		window.draw(sprite);
	}

	void Player::SetDirection(const PlayerDirection newDirection)
	{
		direction = newDirection;
	}

	void Player::SetSpeed(const float newSpeed)
	{
		speed = newSpeed;
	}

	void Player::SetPosition(const Position2D newPosition)
	{
		position.x = newPosition.x;
		position.y = newPosition.y;
	}

	Position2D Player::GetPosition() const
	{
		return position;
	}

	void Player::UpdatePosition(const float deltaTime)
	{
		switch (direction)
		{
		case PlayerDirection::Right:
		{
			position.x += speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			position.y -= speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			position.x -= speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			position.y += speed * deltaTime;
			break;
		}
		}
	}

	float Player::GetSpeed() const
	{
		return speed;
	}

	Circle Player::GetCollider()
	{
		return Circle{position, PLAYER_SIZE / 2.f};
	}
}

