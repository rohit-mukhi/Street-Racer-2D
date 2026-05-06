#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "utils/Constants.h"
#include "utils/LoadingScreen.h"
#include "utils/Road.h"
#include "utils/Player.h"
#include "utils/Enemy.h"
#include "utils/HUD.h"
#include "utils/Audio.h"

// Definitions of extern variables
int WIN_W;
int WIN_H;
float ROAD_LEFT;
float ROAD_RIGHT;

int main()
{
    srand((unsigned)time(nullptr));

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    WIN_W      = desktop.width;
    WIN_H      = desktop.height;
    ROAD_LEFT  = (WIN_W - ROAD_W) / 2.f;
    ROAD_RIGHT = ROAD_LEFT + ROAD_W;

    sf::RenderWindow window(desktop, "Street Racer 2D", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    LoadingScreen loadingScreen;
    Road          road;
    Player        player;
    EnemyManager  enemies;
    HUD           hud;
    Audio         audio;

    audio.play();

    GameState state = GameState::Loading;
    int  score = 0;

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        // ── Events ───────────────────────────────────────────────────────────
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                // Exit fullscreen
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                // Cycle background music
                if (event.key.code == sf::Keyboard::T)
                    audio.nextTrack();

                // Loading → Playing
                if (state == GameState::Loading &&
                    event.key.code == sf::Keyboard::Enter)
                {
                    state = GameState::Playing;
                    clock.restart();
                }

                // Game Over → restart
                if (state == GameState::GameOver &&
                    event.key.code == sf::Keyboard::R)
                {
                    score  = 0;
                    state  = GameState::Playing;
                    player.reset();
                    enemies.reset();
                    audio.play();
                    clock.restart();
                }
            }
        }

        // ── Update ───────────────────────────────────────────────────────────
        if (state == GameState::Playing)
        {
            player.update(dt);
            road.update(dt, enemies.enemySpeed);

            bool gameOver = false;
            score += enemies.update(dt, player.bounds(), gameOver);
            if (gameOver)
            {
                state = GameState::GameOver;
                audio.stop();
            }

            hud.updateScore(score);
        }

        // ── Draw ─────────────────────────────────────────────────────────────
        window.clear();

        if (state == GameState::Loading)
        {
            loadingScreen.draw(window);
        }
        else
        {
            road.draw(window);
            enemies.draw(window);
            player.draw(window);
            hud.draw(window, state == GameState::GameOver, score);
        }

        window.display();
    }

    return 0;
}
