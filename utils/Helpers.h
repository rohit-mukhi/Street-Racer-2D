#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

inline float laneCenterX(int lane)
{
    return ROAD_LEFT + lane * LANE_W + LANE_W / 2.f - PLAYER_W / 2.f;
}

inline void fitSprite(Sprite &spr, float targetW, float targetH)
{
    FloatRect b = spr.getLocalBounds();
    spr.setScale(targetW / b.width, targetH / b.height);
}
