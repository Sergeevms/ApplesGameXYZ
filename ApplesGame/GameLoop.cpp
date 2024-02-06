#include "GameLoop.h"

ApplesGame::GameLoop::GameLoop()
{
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples games!");
	game = new Game();
	game->Init();
}

ApplesGame::GameLoop::~GameLoop()
{
	if (game != nullptr)
	{
		delete game;
	}
	if (window != nullptr)
	{
		delete window;
	}
}

void ApplesGame::GameLoop::Run()
{
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (!game->IsGameShuttingDown() && window->isOpen())
	{

		sf::sleep(sf::milliseconds(15));

		const float currentTime = gameClock.getElapsedTime().asSeconds();
		const float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//Handle events
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				break;
			}
		}

		game->Update(deltaTime);
		window->clear();
		game->Draw(*window);
		window->display();
	}
}
