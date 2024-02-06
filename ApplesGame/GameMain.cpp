// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

/*#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"*/
#include "GameLoop.h"


int main()
{
	using namespace ApplesGame;
	const int seed = (int)time(nullptr);
	srand(seed);

	GameLoop mainLoop;
	mainLoop.Run();

	return 0;
}
