#include <vector>
#include "ReturnToMenuDialogState.h"
#include "ReturnToMenuDialogStateUI.h"
#include "Utility.h"
#include "Constants.h"

namespace ApplesGame
{
	void ReturnToMenuDialogStateUI::Init(sf::Font& textFont)
	{
		returnToMainMenuText.setFont(textFont);
		returnToMainMenuText.setCharacterSize(30);
		returnToMainMenuText.setString("Want to quit game?");

		buttonToPressText.setFont(textFont);
		buttonToPressText.setCharacterSize(30);
		buttonToPressText.setString("Press Y to quit, N to return");

		hintText.setString("Press ESC to return");
		hintText.setPosition(0.f, 0.f);
		hintText.setFillColor(sf::Color::White);
		hintText.setCharacterSize(15);
	}
	void ReturnToMenuDialogStateUI::Draw(sf::RenderWindow& window) const
	{
		window.draw(hintText);
		std::vector<sf::Text*> textToDraw;
		textToDraw.push_back(&returnToMainMenuText);
		textToDraw.push_back(&buttonToPressText);
		
		DrawTexts(window, textToDraw, Position2D{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f }, RelativeOrigin{ 0.5f, 0.5f },
			Alignment::Middle, Orientation::Vertical, true, 10.f);
		
	}
}