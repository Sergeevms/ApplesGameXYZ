#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 120.f;
	const float ACCELERATION = 10.f;
	const float PLAYER_SIZE = 20.f;
	const int MIN_APPLES = 33;
	const int MAX_APPLES = 49;
	const float APPLE_SIZE = 20.f;
	const float RESTART_TIME = 5.f;
	const int NUM_ROCKS = 13;
	const float ROCK_SIZE = 30.f;
	const float NO_ROCKS_ZONE = 8.f; // Set zone where will be no rocks in PLAYER_SIZEs
}