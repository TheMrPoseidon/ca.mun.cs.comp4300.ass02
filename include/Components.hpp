#pragma once

#include <SFML/Graphics.hpp>

#include "Vec2.hpp"

class CTransform
{
public:
    Vec2 pos = {0.0, 0.0};
    Vec2 velocity = {0.0, 0.0};
    Vec2 scale = {1.0, 1.0};
    float angle = 0;
    CTransform(const Vec2 &p, const Vec2 &v, Vec2 s, float a)
        : pos(p), velocity(v), scale(s), angle(a) {}
};

class CShape
{
public:
    sf::CircleShape circle;

    CShape(float radius, size_t points, const sf::Color &fill, const sf::Color &outline, float thickness)
        : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

class CCollision
{
public:
    float radius = 0;

    CCollision(float r)
        : radius(r) {}
};

class CScore
{
public:
    int score = 0;

    CScore(int s)
        : score(s) {}
};

class CLifespan
{
public:
    // total initial lifespan
    int total = 0;

    // remaining lifespan
    int remaining = 0;

    CLifespan(int total)
        : total(total), remaining(total) {}
};

class CInput
{
public:
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;
    bool special = false;
    CInput() {}
};