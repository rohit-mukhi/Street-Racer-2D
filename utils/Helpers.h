#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

// Returns the left-edge X position for a sprite centered in the given lane
inline float laneCenterX(int lane)
{
    return ROAD_LEFT + lane * LANE_W + LANE_W / 2.f - PLAYER_W / 2.f;
}

// Scales a sprite uniformly to fit exactly (targetW x targetH)
inline void fitSprite(sf::Sprite &spr, float targetW, float targetH)
{
    sf::FloatRect b = spr.getLocalBounds();
    spr.setScale(targetW / b.width, targetH / b.height);
}
