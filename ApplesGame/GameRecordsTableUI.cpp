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
	hintText.setCharacterSize(15);
	hintText.setPosition(sf::Vector2f{ 0.f, 0.f });
	if (fromMenu)
	{
		hintText.setString("Press Esc to return\nTab or left/right arrow \nto show table \nfor another mode");
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
		std::multimap<int, std::string> orderedData;		
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
			currentString.append(": ");
			currentString.append(std::to_string((*item).first));
			currentText.setString(currentString);
		}		
	}

	//Header for the table
	headerTexts.reserve(3);
	for (int i = 0; i < 3; ++i)
	{
		headerTexts.emplace_back(sf::Text());
		headerTexts.back().setFont(newFont);
		headerTexts.back().setCharacterSize(30);;
		headerTexts.back().setFillColor(sf::Color::Green);
		headerTexts.back().setStyle(sf::Text::Bold);
	}
	headerTexts[0].setString("Record table of");
	headerTexts[2].setString("game mode:");
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

	switch (selectedGameMode)
	{
	case GameModes::FiniteApllesWithAcceleration:
		headerTexts[1].setString("finite apples with acceleration");
		break;
	case GameModes::FiniteApplesWithoutAcceleration:
		headerTexts[1].setString("finite apples without acceleration");
		break;
	case GameModes::InfiniteApplesWithAcceleartion:
		headerTexts[1].setString("infinite apples with acceleration");
		break;
	case GameModes::InfinteApplesWithoutAcceleration:
		headerTexts[1].setString("infinite apples without acceleration");
		break;
	}

	std::vector<sf::Text*> texts;
	std::vector<sf::Text> currentTexts = orderedTexts[selectedGameMode];
	texts.reserve(headerTexts.size() + currentTexts.size());
	for (auto& text : headerTexts)
	{
		texts.push_back(&text);
	}
	for (auto& text : currentTexts)
	{
		texts.push_back(&text);
	}

	DrawTexts(window, texts, Position2D{ SCREEN_WIDTH / 2.f, TEXT_SPACING}, RelativeOrigin{ 0.5f, 0.f }, 
		Alignment::Middle, Orientation::Vertical, 10.f);
}
