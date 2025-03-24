#include <algorithm>
#include "MenuNode.h"

namespace ApplesGame
{
	void initMenuNode(MenuNode* node, const sf::Font& font, const sf::String& headerString, const sf::String& normalString, 
		Orientation subMenuOrientation,	Alignment subMenuAlignment, float subMenuSpacing)
	{
		node->subMenuAlignment = subMenuAlignment;
		node->subMenuOrientation = subMenuOrientation;
		node->subMenuSpacing = subMenuSpacing;

		node->text.setFont(font);
		node->text.setString(normalString);
		node->text.setCharacterSize(40);
		setStyleNotActive(node);
		
		node->headerText.setFont(font);
		node->headerText.setString(headerString);
		node->headerText.setCharacterSize(60);
	}

	void setStyleActive(MenuNode* node)
	{
		node->text.setFillColor(sf::Color::Yellow);
		node->text.setStyle(sf::Text::Bold | sf::Text::Italic);
	}

	void setStyleNotActive(MenuNode* node)
	{
		node->text.setFillColor(sf::Color::White);
		node->text.setStyle(sf::Text::Regular);
	}

	void selectNextChildNode(MenuNode* node)
	{
		if (node->selectedChild)
		{
			setStyleNotActive(node->selectedChild);
		}
		auto childNodesIterator = std::find(node->childNodes.begin(), node->childNodes.end(), node->selectedChild);
		if (childNodesIterator == node->childNodes.end() - 1 or childNodesIterator == node->childNodes.end())
		{
			node->selectedChild = *(node->childNodes.begin());
		}
		else
		{
			node->selectedChild = *(++childNodesIterator);
		}
		setStyleActive(node->selectedChild);
	}

	void selectPreviosChildNode(MenuNode* node)
	{		
		if (node->selectedChild)
		{
			setStyleNotActive(node->selectedChild);
		}
		auto childNodesIterator = std::find(node->childNodes.rbegin(), node->childNodes.rend(), node->selectedChild);
		if (childNodesIterator == node->childNodes.rend() - 1 or childNodesIterator == node->childNodes.rend())
		{
			node->selectedChild = *(node->childNodes.rbegin());
		}
		else
		{
			node->selectedChild = *(++childNodesIterator);
		}
		setStyleActive(node->selectedChild);
	}

	void addChildNode(MenuNode* node, MenuNode* newChildNode)
	{
		node->expandable = true;
		node->childNodes.emplace_back(newChildNode);
		newChildNode->parentNode = node;
	}
}