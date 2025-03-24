#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utility.h"

namespace ApplesGame
{
	struct MenuNode
	{		
		MenuNode* parentNode{ nullptr };
		MenuNode* selectedChild{ nullptr };

		bool expandable{ false };
		float subMenuSpacing;
		Alignment subMenuAlignment;
		Orientation subMenuOrientation;
		std::vector<MenuNode*> childNodes;
				
		sf::Text text;
		sf::Text headerText;
	};

	void initMenuNode(MenuNode * node, const sf::Font& font, const sf::String& headerString, const sf::String& normalString, 
		Orientation subMenuOrientation = Orientation::Vertical, Alignment subMenuAlignment = Alignment::Middle, float subMenuSpacing = 20.f);
	void addChildNode(MenuNode* node, MenuNode* childeNode);
	void setStyleActive(MenuNode* node);
	void setStyleNotActive(MenuNode* node);
	void selectNextChildNode(MenuNode* node);
	void selectPreviosChildNode(MenuNode* node);
}