#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	class Player
	{
		Position2D position;
		float speed;
		PlayerDirection direction;
		sf::Sprite sprite;
	public:
		void Init(const sf::Texture& playerTexture);
		void Draw(sf::RenderWindow& window);
		void SetDirection(const PlayerDirection newDirection);
		void SetSpeed(const float newPlayerSpeed);
		void SetPosition(const Position2D newPosition);
		Position2D GetPosition() const;
		float GetSpeed() const;
		void UpdatePosition(const float deltaTime);
		Circle GetCollider();
	};

	
}