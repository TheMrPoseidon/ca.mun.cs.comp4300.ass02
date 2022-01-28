#include "Vec2.hpp"

#include <cmath>

Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{
}

// TODO
// Implement all operators

bool Vec2::operator==(const Vec2 &other) const
{
    return (x == other.x && y == other.y);
}

bool Vec2::operator!=(const Vec2 &other) const
{
    return (x != other.x || y != other.y);
}

Vec2 Vec2::operator+(const Vec2 &rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 &rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float val) const
{
    return Vec2(x * val, y * val);
}

Vec2 Vec2::operator/(const float val) const
{
    return Vec2(x / val, y / val);
}

void Vec2::operator+=(const Vec2 &rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator-=(const Vec2 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator*=(const float val)
{
    x *= val;
    y *= val;
}

void Vec2::operator/=(const float val)
{
    x /= val;
    y /= val;
}

// source: https://github.com/ProkopHapala/SimpleSimulationEngine/blob/master/cpp/common/math/Vec2.h

float Vec2::dist(const Vec2 & rhs) const
{
    return sqrtf(dist2(rhs));
}

float Vec2::dist2(const Vec2 & rhs) const
{
    float dx = x-rhs.x; 
    float dy = y-rhs.y; 
    return dx*dx + dy*dy;
}