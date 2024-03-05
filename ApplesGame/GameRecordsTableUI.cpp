#include "GameRecordsTableUI.h"
#include <map>
#include <sstream>
#include <iomanip>
#include "Utility.h"
#include "Math.h"
#include "Constants.h"

void ApplesGame::GameRecordsTableUI::Init(const sf::Font& newFont, std::unordered_map<GameModes, std::unordered_map<std::string, int>>& recordTableData, bool fromMenu) 
{	
	fromMainMenu = fromMenu;

	hintText.setFont(newFont);
	hintText.setCharacterSize(20);
	hintText.setPosition(sf::Vector2f{ 0.f, 0.f });
	if (fromMenu)
	{
		hintText.setString("Press Esc to return\nTab or left/right arrow to show table for another mode");
	}
	else
	{
		hintText.setString("Press Esc to go to main menu");
	}

	mainMenuTimerText.setFont(newFont);
	mainMenuTimerText.setCharacterSize(15);

	orderedTexts.reserve(GAME_MODES_COUNT);
	for (int i = 0; i < GAME_MODES_COUNT; ++i)
	{
		GameModes currentMode = GameModes(i);
		std::map<int, std::string> orderedData;		
		std::unordered_map<std::string, int>& currentUnorderedMap = recordTableData[currentMode];

		for (const auto& item : currentUnorderedMap)
		{
			orderedData.emplace(item.second, item.first);
		}
		
		orderedTexts[currentMode].reserve(RECORDS_TABLE_SIZE);
		int stringNumber = 0;
		for (auto item = orderedData.rbegin(); item != orderedData.rend() && stringNumber < RECORDS_TABLE_SIZE; ++item, ++stringNumber)
		{
			orderedTexts[currentMode].emplace_back(sf::Text());
			sf::Text& currentText = orderedTexts[currentMode].back();

			currentText.setCharacterSize(25);
			currentText.setFillColor((*item).second != PLAYER_NAME ? sf::Color::White : sf::Color::Yellow);
			currentText.setFont(newFont);
			std::string currentString;
			currentString.append(std::to_string(stringNumber + 1));
			currentString.append(". ");
			currentString.append((*item).second);
			currentText.setString(currentString);
		}
	}

	headerText.setFont(newFont);
	headerText.setCharacterSize(40);;
	headerText.setFillColor(sf::Color::Green);
	headerText.setStyle(sf::Text::Bold);
}

void ApplesGame::GameRecordsTableUI::Draw(sf::RenderWindow& window, GameModes selectedGameMode, float timeToMainMenu)
{
	window.draw(hintText);

	if (!fromMainMenu)
	{
		std::stringstream gameRestartText = {};
		gameRestartText << "Goin to main menu automatically in " << std::setprecision(0) << std::fixed << (timeToMainMenu) << " seconds";
		mainMenuTimerText.setString(gameRestartText.str());
		SetOriginByRelative(mainMenuTimerText, RelativeOrigin{ 0.5f, 1.f });
		mainMenuTimerText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - TEXT_SPACING);
		window.draw(mainMenuTimerText);
	}

	std::vector<sf::Text*> texts;
	texts.reserve(RECORDS_TABLE_SIZE);
	std::vector<sf::Text> currentTexts = orderedTexts[selectedGameMode];
	for (auto& text : currentTexts)
	{
		texts.push_back(&text);
	}

	std::string headerString{ "Record table of \n" };
	switch (selectedGameMode)
	{
	case GameModes::FiniteApllesWithAcceleration:
		headerString.append("finite apples with acceleration");
		break;
	case GameModes::FiniteApplesWithoutAcceleration:
		headerString.append("finite apples without acceleration");
		break;
	case GameModes::InfiniteApplesWithAcceleartion:
		headerString.append("infinite apples with acceleration");
		break;
	case GameModes::InfinteApplesWithoutAcceleration:
		headerString.append("infinite apples without acceleration");
		break;
	}
	headerString.append("\n game mode:");
	headerText.setString(headerString);
	headerText.setPosition(SCREEN_WIDTH / 2.f, 0);
	SetOriginByRelative(headerText, RelativeOrigin{ 0.5f, 0.f });

	DrawTexts(window, texts, Position2D{ SCREEN_WIDTH / 2.f, headerText.getGlobalBounds().height }, RelativeOrigin{ 0.5f, 0.f }, 
		Alignment::Min, Orientation::Vertical, TEXT_SPACING);
}
