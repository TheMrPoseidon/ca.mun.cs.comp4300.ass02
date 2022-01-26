#include "Vec2.hpp"

Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{
}

// TODO
// Implement all operators

Vec2 Vec2::operator+(const Vec2 &rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 &rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}