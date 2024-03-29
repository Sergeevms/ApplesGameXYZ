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
