#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "Constants.h"
#include "Helpers.h"

using namespace sf;

struct Enemy
{
    Sprite sprite;
    float  speed;
};

struct EnemyManager
{
    std::vector<Texture> textures;
    std::vector<Enemy>   enemies;

    float spawnTimer = 0.f;
    float enemySpeed = INITIAL_ENEMY_SPD;
    float speedTimer = 0.f;

    EnemyManager()
    {
        textures.resize(3);
        textures[0].loadFromFile("Assets/camaro.png");
        textures[1].loadFromFile("Assets/nissan.png");
        textures[2].loadFromFile("Assets/porsche.png");
    }

    void reset()
    {
        enemies.clear();
        spawnTimer = 0.f;
        speedTimer = 0.f;
        enemySpeed = INITIAL_ENEMY_SPD;
    }

    int update(float dt, const FloatRect &playerBounds, bool &gameOver)
    {
        spawnTimer += dt;
        if (spawnTimer >= SPAWN_INTERVAL)
        {
            spawnTimer = 0.f;
            spawn();
        }

        speedTimer += dt;
        if (speedTimer >= SPEED_BOOST_INTERVAL)
        {
            speedTimer = 0.f;
            enemySpeed = std::min(enemySpeed + SPEED_TIME_BOOST, MAX_ENEMY_SPD);
        }

        for (auto &e : enemies)
            e.sprite.move(0, e.speed * dt);

        int before = (int)enemies.size();
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy &e){ return e.sprite.getPosition().y > WIN_H; }),
            enemies.end());
        int dodged = before - (int)enemies.size();

        for (auto &e : enemies)
        {
            if (playerBounds.intersects(e.sprite.getGlobalBounds()))
            {
                gameOver = true;
                break;
            }
        }

        return dodged * 10;
    }

    void draw(RenderWindow &window)
    {
        for (auto &e : enemies) window.draw(e.sprite);
    }

private:
    void spawn()
    {
        int lane   = rand() % NUM_LANES;
        int texIdx = rand() % (int)textures.size();

        Enemy e;
        e.speed = enemySpeed;
        e.sprite.setTexture(textures[texIdx]);
        fitSprite(e.sprite, ENEMY_W, ENEMY_H);

        if (texIdx == 1)
        {
            e.sprite.setOrigin(ENEMY_W / 2.f, ENEMY_H / 2.f);
            e.sprite.setRotation(180.f);
            e.sprite.setPosition(laneCenterX(lane) + ENEMY_W / 2.f, -ENEMY_H / 2.f);
        }
        else
        {
            e.sprite.setPosition(laneCenterX(lane), -ENEMY_H);
        }

        enemies.push_back(e);
        enemySpeed = std::min(enemySpeed + SPEED_INCREMENT, MAX_ENEMY_SPD);
    }
};
