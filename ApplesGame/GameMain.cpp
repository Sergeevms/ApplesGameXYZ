// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"


int main()
{
	using namespace ApplesGame;
	const int seed = (int)time(nullptr);
	srand(seed);
	//init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples games!");
			
	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	Game game;
	InitGame(game);

	while (window.isOpen())
	{

		sf::sleep(sf::milliseconds(15));

		const float currentTime = gameClock.getElapsedTime().asSeconds();
		const float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
			}
		}

		UpdateGame(game, deltaTime);
		window.clear();
		DrawGame(window, game);
		window.display();
	}
	return 0;
}
