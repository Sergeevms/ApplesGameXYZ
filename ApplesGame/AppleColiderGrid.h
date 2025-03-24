#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Math.h"
#include "Apple.h"
#include "Player.h"

namespace ApplesGame
{
	class AppleColliderGrid
	{		
		std::unordered_multimap<int, int>  grid;
		int gridHeight = 0;
		int gridWidth = 0;
		//std::vector<std::list<int>> grid;
		int GetGridCellID(const Position2D& position) const;
	public:
		void SetGridSize(const int height, const int width);
		void InsertApple(const Apple& apple, const int appleID);
		void EraseApple(const Apple& apple, const int appleID);
		void Clear();
		std::unordered_set<int> GetNearestAppleIDsList(const Player& player);
	};
}