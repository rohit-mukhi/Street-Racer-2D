#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

struct LoadingScreen
{
    sf::Texture bgTexture;
    sf::Sprite  bgSprite;
    sf::Font    font;
    sf::Text    titleText;
    sf::Text    promptText;

    LoadingScreen()
    {
        // Background
        bgTexture.loadFromFile("Assets/loading_screen.png");
        bgSprite.setTexture(bgTexture);

        // Scale background to fill the window
        sf::Vector2u texSize = bgTexture.getSize();
        bgSprite.setScale((float)WIN_W / texSize.x, (float)WIN_H / texSize.y);

        // Font
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
            if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf"))
                font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSansBold.ttf");

        // Title
        titleText.setFont(font);
        titleText.setString("Street Racer 2D");
        titleText.setCharacterSize(58);
        titleText.setFillColor(sf::Color::White);
        titleText.setOutlineColor(sf::Color::Black);
        titleText.setOutlineThickness(3);
        sf::FloatRect tb = titleText.getLocalBounds();
        titleText.setOrigin(tb.width / 2.f, tb.height / 2.f);
        titleText.setPosition(WIN_W / 2.f, WIN_H / 2.f - 40.f);

        // Prompt
        promptText.setFont(font);
        promptText.setString("Press Enter to Start");
        promptText.setCharacterSize(28);
        promptText.setFillColor(sf::Color(220, 220, 220));
        promptText.setOutlineColor(sf::Color::Black);
        promptText.setOutlineThickness(2);
        sf::FloatRect pb = promptText.getLocalBounds();
        promptText.setOrigin(pb.width / 2.f, pb.height / 2.f);
        promptText.setPosition(WIN_W / 2.f, WIN_H / 2.f + 40.f);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(bgSprite);
        window.draw(titleText);
        window.draw(promptText);
    }
};
