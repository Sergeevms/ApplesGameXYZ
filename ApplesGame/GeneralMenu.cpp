#include <assert.h>
#include "GeneralMenu.h"
#include "Constants.h"
#include "Utility.h"

namespace ApplesGame
{

	bool GeneralMenu::ExpandSelected()
	{
		if (currentNode->selectedChild->expandable)
		{
			currentNode = currentNode->selectedChild;
			currentNode->selectedChild = *(currentNode->childNodes.begin());
			setStyleActive(currentNode->selectedChild);
			return true;
		}
		else
		{
			return false;
		}
	}

	void GeneralMenu::ReturnToPrevios()
	{
		if (currentNode->parentNode)
		{
			if (currentNode->selectedChild)
			{
				setStyleNotActive(currentNode->selectedChild);
			}			
			currentNode = currentNode->parentNode;
		}
	}

	void GeneralMenu::Draw(sf::RenderWindow& window)
	{
		std::vector<sf::Text*> menuTexts;
		menuTexts.reserve(currentNode->childNodes.size());
		SetOriginByRelative(currentNode->headerText, RelativeOrigin{ 0.5f, 0.f });
		currentNode->headerText.setPosition(SCREEN_WIDTH / 2.f, 10.f);
		sf::FloatRect headerRect = currentNode->headerText.getGlobalBounds();
		Position2D headerBottom{ SCREEN_WIDTH / 2.f, HEADER_SPACING + headerRect.height };
		for (auto& child : currentNode->childNodes)
		{
			menuTexts.push_back(&child->text);
		}
		window.draw(currentNode->headerText);
		DrawTexts(window, menuTexts, Position2D{ headerBottom }, RelativeOrigin{ 0.5f, 0.f }, currentNode->subMenuAlignment,
			currentNode->subMenuOrientation, currentNode->subMenuSpacing);
	}
}