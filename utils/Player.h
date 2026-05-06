#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Helpers.h"

struct Player
{
    sf::Texture texture;
    sf::Sprite  sprite;

    // =========================================================================
    // PLAYER TEXTURE — change the path to the car you want the player to drive
    // =========================================================================
    Player()
    {
        texture.loadFromFile("Assets/audi.png");   // <-- CHANGE THIS
        sprite.setTexture(texture);
        fitSprite(sprite, PLAYER_W, PLAYER_H);
        sprite.setOrigin(PLAYER_W / 2.f, PLAYER_H / 2.f);
        sprite.setRotation(180.f);
        reset();
    }

    void reset()
    {
        // Offset by half size to compensate for centered origin
        sprite.setPosition(laneCenterX(NUM_LANES / 2) + PLAYER_W / 2.f,
                           WIN_H - PLAYER_H / 2.f - 20.f);
    }

    void update(float dt)
    {
        float px = sprite.getPosition().x;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  px -= PLAYER_SPD * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) px += PLAYER_SPD * dt;
        // Clamp: origin is at center, so bounds are [center - half, center + half]
        px = std::max(px, ROAD_LEFT  + PLAYER_W / 2.f);
        px = std::min(px, ROAD_RIGHT - PLAYER_W / 2.f);
        sprite.setPosition(px, sprite.getPosition().y);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

    sf::FloatRect bounds() const
    {
        return sprite.getGlobalBounds();
    }
};
