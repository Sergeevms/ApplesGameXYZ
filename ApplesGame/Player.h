#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Game;

	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		Position2D playerPosition;
		float playerSpeed;
		PlayerDirection playerDirection;
		sf::Sprite sprite;
	};

	void InitPlayer(Player& player, const Game& game);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
	void SetPlayerDirection(Player& player, const PlayerDirection playerDirection);
	void SetPlayerSpeed(Player& player, const float playerSpeed);
	void SetPlayerPosition(Player& player, const Position2D position);
	float GetPlayerSpeed(const Player& player);
	void UpdatePlayerPosition(Player& player, const float deltaTime);
	Circle GetPlayerCollider(const Player& player);
}