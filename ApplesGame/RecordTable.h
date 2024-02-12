#pragma once

#include <vector>
#include <fstream>
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
		RecordTable(const std::vector<std::string>& playerNames, int recordTableSize, int maxScore, const sf::Font& textFont, short currentGameMode);
		void UpdatePlayerScore(int playerScore);
		void Draw(sf::RenderWindow&) const;
	};
}
