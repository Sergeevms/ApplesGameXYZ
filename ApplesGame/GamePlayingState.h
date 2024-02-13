#pragma once
#include "GameStateBase.h"
#include "Player.h"
#include "Rock.h"
#include "ApplesMassive.h"
#include "AppleColiderGrid.h"
#include "GamePlayingStateUI.h"

namespace ApplesGame
{
    class GamePlayingState:
        public GameStateBase
    {
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::Font textFont;

        sf::SoundBuffer appleEatenSoundBuffer;
        sf::SoundBuffer playerDeathSoundBuffer;

        sf::Sound appleEatenSound;
        sf::Sound playerDeathSound;

        GamePlayingStateUI stateUI;
        Player player;
        ApplesMassive apples;
        std::vector<Rock> rocks;
        Rectangle windowRectangle;
        Rectangle noRocksRectangle;
        AppleColliderGrid appleCollderGrid;
        GameModes currentGameMode;
        Game* game = nullptr;
        int numEatenApples;
        float gameStateTimer;

    public:
        GamePlayingState(Game* currentGame, int finiteApplesCount);
        void Start() override;
        void Update(const float deltaTime) override;
        void Draw(sf::RenderWindow& window);
        void End() override;
    };
}
