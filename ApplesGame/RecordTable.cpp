#include <fstream>
#include <algorithm>
#include "RecordTable.h"
#include "Game.h"
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{	
	RecordTable::RecordTable(const std::vector<std::string>& playerNames, int recordTableSize, int maxScore, const sf::Font& textFont, short gameMode)
	{
		playerScoreIndex = RECORDS_TABLE_SIZE - 1;
		recordTableData.reserve(RECORDS_TABLE_SIZE);
		recordTableRowsText.reserve(RECORDS_TABLE_SIZE);
		std::vector<RecordTableRow> currentSet;
		for (std::string i : playerNames)
		{
			currentSet.push_back(RecordTableRow(GetRandomIntInRange(0, maxScore), i));
		}
		std::sort(currentSet.begin(), currentSet.end(), [](const RecordTableRow& a, const RecordTableRow& b) {return a.first > b.first; });
		for (int i = 0; i < RECORDS_TABLE_SIZE - 1; ++i)
		{
			recordTableData.push_back(currentSet[i]);
		}
		recordTableData.push_back(RecordTableRow(0, "Player"));

		std::string headerText{ "Record table of " };
		switch (gameMode)
		{
		case Game::GameModes::FiniteApllesWithAcceleration:
			headerText.append("finite apples with acceleration");
			break;
		case Game::GameModes::FiniteApplesWithoutAcceleration:
			headerText.append("finite apples without acceleration");
			break;
		case Game::GameModes::InfiniteApplesWithAcceleartion:
			headerText.append("infinite apples with acceleration");
			break;
		case Game::GameModes::InfinteApplesWithoutAcceleration:
			headerText.append("infinite apples without acceleration");
			break;
		}
		headerText.append(" game mode:");
		header.setFont(textFont);
		header.setCharacterSize(textSize);
		header.setString(headerText);
		header.setFillColor(sf::Color::Green);
		header.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f - header.getGlobalBounds().width / 2.f, 0.f));
		header.setStyle(sf::Text::Bold);

		for (int i = 0; i < RECORDS_TABLE_SIZE; ++i)
		{
			recordTableRowsText.push_back(sf::Text());
			recordTableRowsText[i].setCharacterSize(textSize);
			recordTableRowsText[i].setFont(textFont);
			UpdateRowTextAndPlayerIndex(i);
		}
	}

	void RecordTable::UpdatePlayerScore(int playerScore)
	{
		recordTableData[playerScoreIndex].first = playerScore;
		std::sort(recordTableData.begin(), recordTableData.end(), [](const RecordTableRow& a, const RecordTableRow& b) {return a.first > b.first; });
		for (int i = 0; i < RECORDS_TABLE_SIZE; ++i)
		{
			UpdateRowTextAndPlayerIndex(i);
		}
	}

	void RecordTable::UpdateRowTextAndPlayerIndex(int i)
	{
		std::string currentRow = std::to_string(i + 1);
		currentRow.append(". ");
		currentRow.append(recordTableData[i].second);
		currentRow.append(" ");
		currentRow.append(std::to_string(recordTableData[i].first));
		recordTableRowsText[i].setString(currentRow);
		if (recordTableData[i].second != std::string("Player"))
		{
			recordTableRowsText[i].setFillColor(sf::Color::White);
			recordTableRowsText[i].setStyle(sf::Text::Regular);
		}
		else
		{
			recordTableRowsText[i].setFillColor(sf::Color::Yellow);
			recordTableRowsText[i].setStyle(sf::Text::Bold | sf::Text::Italic);
			playerScoreIndex = i;
		}
		recordTableRowsText[i].setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f - recordTableRowsText[i].getGlobalBounds().width / 2.f,
			2.f * header.getGlobalBounds().height + i * header.getGlobalBounds().height));
	}

	const void RecordTable::Draw(sf::RenderWindow& window)
	{
		window.draw(header);
		for (sf::Text row : recordTableRowsText)
		{
			window.draw(row);
		}
	}
}