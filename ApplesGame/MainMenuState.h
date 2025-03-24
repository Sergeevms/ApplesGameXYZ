#pragma once
#include "GameStateBase.h"
#include "GeneralMenu.h"

namespace ApplesGame
{
    class Game;
    enum GameModes;

    struct MainMenu : public GeneralMenu
    {
        MenuNode root;
        MenuNode play;
        MenuNode options;
        MenuNode infiniteAppleOption;
        MenuNode accelerationOption;
        MenuNode recordsTable;
        MenuNode exit;
        MenuNode yesOnExit;
        MenuNode noOnExit;

        MainMenu();
        void UpdateOptionsText(GameModes gameMode);
    };

    class MainMenuState :
        public GameStateBase
    {
        Game* game;
        MainMenu menu;

    public:
        MainMenuState(Game * currentGame);
        GameState GetGameState() const override { return GameState::MainMenu; };
        virtual void Update(const float deltaTime) override;
        virtual void Draw(sf::RenderWindow& window) override;
        ~MainMenuState() = default;
    };
}

