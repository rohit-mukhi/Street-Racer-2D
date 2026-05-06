#include <SFML/Graphics.hpp>
#include <sstream>
#include "Constants.h"

using namespace sf;

struct HUD
{
    Font font;
    Text scoreText;
    Text gameOverText;
    Text subText;

    HUD()
    {
        font.loadFromFile("Assets/ttt/TTT-Bold.otf");

        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(10, 10);

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(52);
        gameOverText.setFillColor(Color::Red);
        gameOverText.setString("GAME OVER");

        subText.setFont(font);
        subText.setCharacterSize(26);
        subText.setFillColor(Color::White);
    }

    void updateScore(int score)
    {
        std::ostringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());
    }

    void draw(RenderWindow &window, bool gameOver, int score)
    {
        window.draw(scoreText);

        if (!gameOver) return;

        RectangleShape overlay({(float)WIN_W, (float)WIN_H});
        overlay.setFillColor(Color(0, 0, 0, 150));
        window.draw(overlay);

        FloatRect gb = gameOverText.getLocalBounds();
        gameOverText.setOrigin(gb.width / 2, gb.height / 2);
        gameOverText.setPosition(WIN_W / 2.f, WIN_H / 2.f - 50);
        window.draw(gameOverText);

        std::ostringstream ss;
        ss << "Score: " << score << "\n\nPress R to Restart";
        subText.setString(ss.str());
        FloatRect sb = subText.getLocalBounds();
        subText.setOrigin(sb.width / 2, sb.height / 2);
        subText.setPosition(WIN_W / 2.f, WIN_H / 2.f + 30);
        window.draw(subText);
    }
};
