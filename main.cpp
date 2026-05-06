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

using namespace sf;

int WIN_W;
int WIN_H;
float ROAD_LEFT;
float ROAD_RIGHT;

int main()
{
    srand((unsigned)time(nullptr));

    VideoMode desktop = VideoMode::getDesktopMode();
    WIN_W      = desktop.width;
    WIN_H      = desktop.height;
    ROAD_LEFT  = (WIN_W - ROAD_W) / 2.f;
    ROAD_RIGHT = ROAD_LEFT + ROAD_W;

    RenderWindow window(desktop, "Street Racer 2D", Style::Fullscreen);
    window.setFramerateLimit(60);

    LoadingScreen loadingScreen;
    Road          road;
    Player        player;
    EnemyManager  enemies;
    HUD           hud;
    Audio         audio;

    audio.play();

    GameState state = GameState::Loading;
    int score = 0;

    Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                    window.close();

                if (event.key.code == Keyboard::T)
                    audio.nextTrack();

                if (state == GameState::Loading &&
                    event.key.code == Keyboard::Enter)
                {
                    state = GameState::Playing;
                    clock.restart();
                }

                if (state == GameState::GameOver &&
                    event.key.code == Keyboard::R)
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
