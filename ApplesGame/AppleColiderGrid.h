#pragma once
#include <vector>

#include "Math.h"
#include "Apple.h"
#include "Player.h"

namespace ApplesGame
{
	class AppleColliderGrid
	{
		int gridHeight;
		int gridWidth;
		std::vector<std::vector<int>> grid;

		int GetGridCellIndex(Position2D& position);
	public:
		AppleColliderGrid() : gridHeight {0}, gridWidth {0};
		AppleColliderGrid(int height, int width);
		void SetGridSize(const int height, const int width);
		void InsertApple(const Apple& apple, const int appleID);
		void EraseApple(const Apple& apple, const int appleID);
		void Clear();
		std::vector<int> GetNearestAppleIDsList(const Player& player);
	}

}