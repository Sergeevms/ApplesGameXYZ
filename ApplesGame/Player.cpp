#include "Player.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.playerPosition.x, player.playerPosition.y);

		if (player.playerDirection == PlayerDirection::Left)
		{
			SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(0.f);
		}
		else
		{
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(-90.f * (float)player.playerDirection);
		}
		window.draw(player.sprite);
	}

	void SetPlayerDirection(Player& player, const PlayerDirection playerDirection)
	{
		player.playerDirection = playerDirection;
	}

	void SetPlayerSpeed(Player& player, const float playerSpeed)
	{
		player.playerSpeed = playerSpeed;
	}

	void SetPlayerPosition(Player& player, const Position2D position)
	{
		player.playerPosition.x = position.x;
		player.playerPosition.y = position.y;
	}

	void UpdatePlayerPosition(Player& player, const float deltaTime)
	{
		switch (player.playerDirection)
		{
		case PlayerDirection::Right:
		{
			player.playerPosition.x += player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			player.playerPosition.y -= player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			player.playerPosition.x -= player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			player.playerPosition.y += player.playerSpeed * deltaTime;
			break;
		}
		}
	}

	float GetPlayerSpeed(const Player& player)
	{
		return player.playerSpeed;
	}

	Circle GetPlayerCollider(const Player& player)
	{
		return Circle{player.playerPosition, PLAYER_SIZE / 2.f};
	}
}

