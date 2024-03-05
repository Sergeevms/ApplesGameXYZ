#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Game.h"

namespace ApplesGame
{
	class GameRecordsTableUI
	{
		bool fromMainMenu;
		sf::Text hintText;
		std::vector<sf::Text> headerTexts;
		sf::Text mainMenuTimerText;
		std::unordered_map<GameModes, std::vector<sf::Text>> orderedTexts;
	public:
		void Init(const sf::Font& newFont, std::unordered_map<GameModes, std::unordered_map<std::string, int>>& recordTableData, const bool fromMenu);
		void Draw(sf::RenderWindow& window, const GameModes selectedGameMode, float timeToMainMenu = 0);
	};
}