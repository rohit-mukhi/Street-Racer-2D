#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Constants.h"

struct HUD
{
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text subText;

    HUD()
    {
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
            if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf"))
                font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSansBold.ttf");

        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(52);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("GAME OVER");

        subText.setFont(font);
        subText.setCharacterSize(26);
        subText.setFillColor(sf::Color::White);
    }

    void updateScore(int score)
    {
        std::ostringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());
    }

    void draw(sf::RenderWindow &window, bool gameOver, int score)
    {
        window.draw(scoreText);

        if (!gameOver) return;

        // Dim overlay
        sf::RectangleShape overlay({(float)WIN_W, (float)WIN_H});
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);

        sf::FloatRect gb = gameOverText.getLocalBounds();
        gameOverText.setOrigin(gb.width / 2, gb.height / 2);
        gameOverText.setPosition(WIN_W / 2.f, WIN_H / 2.f - 50);
        window.draw(gameOverText);

        std::ostringstream ss;
        ss << "Score: " << score << "\n\nPress R to Restart";
        subText.setString(ss.str());
        sf::FloatRect sb = subText.getLocalBounds();
        subText.setOrigin(sb.width / 2, sb.height / 2);
        subText.setPosition(WIN_W / 2.f, WIN_H / 2.f + 30);
        window.draw(subText);
    }
};
