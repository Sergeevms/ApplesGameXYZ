#pragma once

#include <vector>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	typedef std::pair<int, std::string> RecordTableRow;

	class RecordTable
	{
		int playerScoreIndex;
		const static int textSize = 20;
		std::vector<RecordTableRow> recordTableData;
		std::vector<sf::Text> recordTableRowsText;
		sf::Text header;
		void UpdateRowTextAndPlayerIndex(int i);
	public:
		RecordTable(const std::vector<std::string>& playerNames, int recordTableSize, int maxScore, const sf::Font& textFont, short gameMode);
		void UpdatePlayerScore(int playerScore);
		const void Draw(sf::RenderWindow&);
	};
}
