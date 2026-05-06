#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

struct LoadingScreen
{
    Texture bgTexture;
    Sprite  bgSprite;
    Font    font;
    Text    titleText;
    Text    promptText;

    LoadingScreen()
    {
        bgTexture.loadFromFile("Assets/loading_screen.png");
        bgSprite.setTexture(bgTexture);

        Vector2u texSize = bgTexture.getSize();
        bgSprite.setScale((float)WIN_W / texSize.x, (float)WIN_H / texSize.y);

        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
            if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf"))
                font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSansBold.ttf");

        titleText.setFont(font);
        titleText.setString("Street Racer 2D");
        titleText.setCharacterSize(58);
        titleText.setFillColor(Color::White);
        titleText.setOutlineColor(Color::Black);
        titleText.setOutlineThickness(3);
        FloatRect tb = titleText.getLocalBounds();
        titleText.setOrigin(tb.width / 2.f, tb.height / 2.f);
        titleText.setPosition(WIN_W / 2.f, WIN_H / 2.f - 40.f);

        promptText.setFont(font);
        promptText.setString("Press Enter to Start");
        promptText.setCharacterSize(28);
        promptText.setFillColor(Color(220, 220, 220));
        promptText.setOutlineColor(Color::Black);
        promptText.setOutlineThickness(2);
        FloatRect pb = promptText.getLocalBounds();
        promptText.setOrigin(pb.width / 2.f, pb.height / 2.f);
        promptText.setPosition(WIN_W / 2.f, WIN_H / 2.f + 40.f);
    }

    void draw(RenderWindow &window)
    {
        window.draw(bgSprite);
        window.draw(titleText);
        window.draw(promptText);
    }
};
