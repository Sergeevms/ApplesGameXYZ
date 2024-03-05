#pragma once
#include "GameStateBase.h"
#include "Player.h"
#include "Rock.h"
#include "ApplesMassive.h"
#include "AppleColiderGrid.h"
#include "GamePlayingStateUI.h"

namespace ApplesGame
{
    class Game;
    enum GameModes;

    class GamePlayingState:
        public GameStateBase
    {
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::Font textFont;

        sf::Sound * appleEatenSound;
        sf::Sound * playerDeathSound;

        GamePlayingStateUI stateUI;
        Player player;
        ApplesMassive apples;
        std::vector<Rock> rocks;
        Rectangle windowRectangle;
        Rectangle noRocksRectangle;
        AppleColliderGrid appleCollderGrid;
        GameModes currentGameMode;
        Game* game;
        int numEatenApples;
        float gameStateTimer;

        void EndGame(bool isWinned = false);

    public:
        GamePlayingState(Game* currentGame, int finiteApplesCount, sf::Sound * appleEatenSound, sf::Sound * playerDeathSound);
        GameState GetGameState() const override { return GameState::Playing; };
        void Update(const float deltaTime) override;
        void Draw(sf::RenderWindow& window);
        ~GamePlayingState() = default;
    };
}
