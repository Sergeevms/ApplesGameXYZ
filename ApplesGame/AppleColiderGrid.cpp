#include "AppleColiderGrid.h"
#include "Constants.h"

namespace ApplesGame
{
	AppleColliderGrid::AppleColliderGrid(const int height, const int width)
	{
		SetGridSize(height, width);
	}

	void AppleColliderGrid::SetGridSize(const int height, const int width)
	{
		gridHeight = height;
		gridWidth = width;
		grid.clear();
		grid.reserve(gridHeight * gridWidth);
		for (int i = 0; i < gridHeight * gridWidth; ++i)
		{
			grid.push_back(std::vector<int>{});
		}
	}

	int AppleColliderGrid::GetGridCellIndex(Position2D& position)
	{
		const float cellHeight = SCREEN_HEIGHT / (float)gridHeight;
		const float cellWidth = SCREEN_WIDTH / (float)gridWidth;

		int cellX = position.x / cellWidth;
		int cellY = position.y / cellHeight;

		return cellY * gridWidth + cellX;
	}

	void AppleColliderGrid::InsertApple(const Apple& apple, const int appleID)
	{
		int cellIndex = GetGridCellIndex(GetPosition(apple));
		grid[cellIndex].push_back(appleID);
	}

	void AppleColliderGrid::EraseApple(const Apple& apple, const int appleID)
	{
		int cellIndex = GetGridCellIndex(GetPosition(apple));
		auto last = std::remove(grid[cellIndex].begin(), grid[cellIndex].end(), appleID);
		grid[cellIndex].erase(last, grid[cellIndex].end());
	}

	void AppleColliderGrid::Clear()
	{
		for (auto& i : grid)
		{
			i.clear();
		}
	}

	std::vector<int> AppleColliderGrid::GetNearestAppleIDsList(const Player& player)
	{
		std::vector<int> appleIDsList;
		int playerCellIndex = GetGridCellIndex(GetPosition(player));
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				int cellIndex = gridWidth * i + j + playerCellIndex;
				if (cellIndex >= 0 and cellIndex < gridHeight * gridWidth)
				{
					for (int appleID : grid[cellIndex])
					{
						appleIDsList.push_back(appleID);
					}
				}
			}
		}
		return appleIDsList;
	}

}