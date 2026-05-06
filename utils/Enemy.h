#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "Constants.h"
#include "Helpers.h"

// ── Single enemy ──────────────────────────────────────────────────────────────
struct Enemy
{
    sf::Sprite sprite;
    float      speed;
};

// ── Manages all active enemies ────────────────────────────────────────────────
struct EnemyManager
{
    std::vector<sf::Texture> textures;
    std::vector<Enemy>       enemies;

    float spawnTimer = 0.f;
    float enemySpeed = INITIAL_ENEMY_SPD;
    float speedTimer = 0.f;   // tracks time for periodic speed boost

    // =========================================================================
    // ENEMY TEXTURES — change paths or add more; enemies pick one at random.
    // Resize the vector to match the number of textures you load.
    // =========================================================================
    EnemyManager()
    {
        textures.resize(3);                                        // <-- resize if needed
        textures[0].loadFromFile("Assets/camaro.png");             // <-- CHANGE THIS
        textures[1].loadFromFile("Assets/nissan.png");             // <-- CHANGE THIS
        textures[2].loadFromFile("Assets/porsche.png");            // <-- CHANGE THIS
    }

    void reset()
    {
        enemies.clear();
        spawnTimer = 0.f;
        speedTimer = 0.f;
        enemySpeed = INITIAL_ENEMY_SPD;
    }

    // Returns points earned this frame (10 per dodged enemy)
    int update(float dt, const sf::FloatRect &playerBounds, bool &gameOver)
    {
        // Spawn
        spawnTimer += dt;
        if (spawnTimer >= SPAWN_INTERVAL)
        {
            spawnTimer = 0.f;
            spawn();
        }

        // Time-based speed boost every 30 seconds
        speedTimer += dt;
        if (speedTimer >= SPEED_BOOST_INTERVAL)
        {
            speedTimer = 0.f;
            enemySpeed = std::min(enemySpeed + SPEED_TIME_BOOST, MAX_ENEMY_SPD);
        }

        // Move
        for (auto &e : enemies)
            e.sprite.move(0, e.speed * dt);

        // Remove off-screen & count dodged
        int before = (int)enemies.size();
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy &e){ return e.sprite.getPosition().y > WIN_H; }),
            enemies.end());
        int dodged = before - (int)enemies.size();

        // Collision
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

    void draw(sf::RenderWindow &window)
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

        // Nissan (index 1) is flipped — rotate 180° around its center
        if (texIdx == 1)
        {
            e.sprite.setOrigin(ENEMY_W / 2.f, ENEMY_H / 2.f);
            e.sprite.setRotation(180.f);
            // With a centered origin the position anchor shifts, so offset by half size
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
