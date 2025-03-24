#pragma once
#include <SFML/Graphics.hpp>

#include "MenuNode.h"

namespace ApplesGame
{

	const float HEADER_SPACING = 60.f;

	struct GeneralMenu
	{
		MenuNode* currentNode{ nullptr };
		sf::Font menuFont;

		virtual bool ExpandSelected();
		virtual void ReturnToPrevios();
		virtual void Draw(sf::RenderWindow& widnow);
	};

	

	
}

