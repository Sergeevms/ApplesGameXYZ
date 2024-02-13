#pragma once
#include "GameStateBase.h"
#include "Game.h"
#include "GameStartingStateUI.h"

namespace ApplesGame
{
    class GameStartingState :
        public GameStateBase
    {
        Game* game;
        sf::Font textFont;
        GameStartingStateUI stateUI;
    public:
        GameStartingState(Game* currentGame);
        void Start();
        void Update();
        void End();
        void Draw(sf::RenderWindow& window);
    };
}

