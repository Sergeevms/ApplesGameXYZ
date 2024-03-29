#include "AppleColiderGrid.h"
#include "Constants.h"

namespace ApplesGame
{
	void AppleColliderGrid::SetGridSize(const int height, const int width)
	{
		gridHeight = height;
		gridWidth = width;
		grid.clear();
	}

	int AppleColliderGrid::GetGridCellID(const Position2D& position) const
	{
		const float cellHeight = SCREEN_HEIGHT / (float)gridHeight;
		const float cellWidth = SCREEN_WIDTH / (float)gridWidth;

		int cellX = (int) (position.x / cellWidth);
		int cellY = (int) (position.y / cellHeight);
		
		return cellY * gridWidth + cellX;
	}

	void AppleColliderGrid::InsertApple(const Apple& apple, const int appleID)
	{
		int cellID = GetGridCellID(apple.GetPosition());
		grid.insert(std::make_pair(cellID, appleID));
	}

	void AppleColliderGrid::EraseApple(const Apple& apple, const int appleID)
	{
		int cellID = GetGridCellID(apple.GetPosition());
		auto bucket = grid.equal_range(cellID);
		for (auto& id = bucket.first; id != bucket.second; )
		{
			if ((*id).second == appleID)
			{
				id = grid.erase(id);
			}
			else
			{
				++id;
			}
		}
	}

	void AppleColliderGrid::Clear()
	{
		grid.clear();
	}

	std::unordered_set<int> AppleColliderGrid::GetNearestAppleIDsList(const Player& player)
	{
		std::unordered_set<int> appleIDsList;
		int playerCellID = GetGridCellID(player.GetPosition());
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				int currentCellID = playerCellID + i * APPLES_COLLIDER_GRID_WIDTH + j;
				auto bucket = grid.equal_range(currentCellID);
				for (auto& appleID = bucket.first; appleID != bucket.second; ++appleID)
				{
					appleIDsList.insert(appleID->second);
				}
			}
		}
		return appleIDsList;
	}

}