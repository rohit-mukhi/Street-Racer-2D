#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"

using namespace sf;

struct DashColumn
{
    std::vector<RectangleShape> dashes;
    float offset = 0.f;

    void init(float x)
    {
        float period = DASH_H + DASH_GAP;
        int count = (int)(WIN_H / period) + 2;
        dashes.resize(count);
        for (int i = 0; i < count; ++i)
        {
            dashes[i].setSize({DASH_W, DASH_H});
            dashes[i].setFillColor(Color(200, 200, 200));
            dashes[i].setPosition(x - DASH_W / 2.f, i * period);
        }
    }

    void update(float dt, float speed)
    {
        float period = DASH_H + DASH_GAP;
        offset += speed * dt;
        if (offset >= period) offset -= period;
        for (int i = 0; i < (int)dashes.size(); ++i)
            dashes[i].setPosition(dashes[i].getPosition().x,
                                  i * period + offset - period);
    }

    void draw(RenderWindow &window)
    {
        for (auto &d : dashes) window.draw(d);
    }
};

struct Road
{
    RectangleShape grass;
    RectangleShape asphalt;
    std::vector<DashColumn> dividers;

    Road()
    {
        grass.setSize({(float)WIN_W, (float)WIN_H});
        grass.setFillColor(Color(34, 100, 34));

        asphalt.setSize({ROAD_W, (float)WIN_H});
        asphalt.setPosition(ROAD_LEFT, 0);
        asphalt.setFillColor(Color(50, 50, 50));

        dividers.resize(NUM_LANES - 1);
        for (int i = 0; i < NUM_LANES - 1; ++i)
            dividers[i].init(ROAD_LEFT + (i + 1) * LANE_W);
    }

    void update(float dt, float speed)
    {
        for (auto &d : dividers) d.update(dt, speed);
    }

    void draw(RenderWindow &window)
    {
        window.draw(grass);
        window.draw(asphalt);
        for (auto &d : dividers) d.draw(window);
    }
};
