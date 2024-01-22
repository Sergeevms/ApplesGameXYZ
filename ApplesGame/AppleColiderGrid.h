#pragma once
#include <vector>
#include <list>

#include "Math.h"
#include "Apple.h"
#include "Player.h"

namespace ApplesGame
{
	class AppleColliderGrid
	{
		int gridHeight;
		int gridWidth;
		std::vector<std::list<int>> grid;

		int GetGridCellIndex(const Position2D& position) const;
	public:
		AppleColliderGrid();
		AppleColliderGrid(int height, int width);
		void SetGridSize(const int height, const int width);
		void InsertApple(const Apple& apple, const int appleID);
		void EraseApple(const Apple& apple, const int appleID);
		void Clear();
		std::list<int> GetNearestAppleIDsList(const Player& player);
	};
}