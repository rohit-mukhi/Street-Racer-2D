#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Helpers.h"

using namespace sf;

struct Player
{
    Texture texture;
    Sprite  sprite;

    Player()
    {
        texture.loadFromFile("Assets/audi.png");
        sprite.setTexture(texture);
        fitSprite(sprite, PLAYER_W, PLAYER_H);
        sprite.setOrigin(PLAYER_W / 2.f, PLAYER_H / 2.f);
        sprite.setRotation(180.f);
        reset();
    }

    void reset()
    {
        sprite.setPosition(laneCenterX(NUM_LANES / 2) + PLAYER_W / 2.f,
                           WIN_H - PLAYER_H / 2.f - 20.f);
    }

    void update(float dt)
    {
        float px = sprite.getPosition().x;
        float py = sprite.getPosition().y;
        if (Keyboard::isKeyPressed(Keyboard::Left))  px -= PLAYER_SPD * dt;
        if (Keyboard::isKeyPressed(Keyboard::Right)) px += PLAYER_SPD * dt;
        px = std::max(px, ROAD_LEFT  + PLAYER_W / 2.f);
        px = std::min(px, ROAD_RIGHT - PLAYER_W / 2.f);
        sprite.setPosition(px, py);
    }

    void draw(RenderWindow &window)
    {
        window.draw(sprite);
    }

    FloatRect bounds() const
    {
        return sprite.getGlobalBounds();
    }
};
