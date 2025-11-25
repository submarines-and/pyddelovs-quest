#include <math.h>
#include "vector2d.h"

Vector2d::Vector2d()
{
    x = y = 0.0f;
}

Vector2d::Vector2d(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2d& Vector2d::add(const Vector2d& vec)
{
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2d& Vector2d::subtract(const Vector2d& vec)
{
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2d& Vector2d::multiply(const Vector2d& vec)
{
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

Vector2d& Vector2d::divide(const Vector2d& vec)
{
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2d& operator+(Vector2d& v1, const Vector2d& v2)
{
    return v1.add(v2);
}
Vector2d& operator-(Vector2d& v1, const Vector2d& v2)
{
    return v1.subtract(v2);
}
Vector2d& operator*(Vector2d& v1, const Vector2d& v2)
{
    return v1.multiply(v2);
}

Vector2d& operator/(Vector2d& v1, const Vector2d& v2)
{
    return v1.divide(v2);
}

Vector2d& Vector2d::operator+=(const Vector2d vec)
{
    return this->add(vec);
}
Vector2d& Vector2d::operator-=(const Vector2d vec)
{
    return this->subtract(vec);
}

Vector2d& Vector2d::operator*=(const Vector2d vec)
{
    return this->multiply(vec);
}
Vector2d& Vector2d::operator/=(const Vector2d vec)
{
    return this->divide(vec);
}

Vector2d& Vector2d::operator*(const int& i)
{
    this->x *= i;
    this->y *= i;

    return *this;
}

/** Set vector to 0*/
Vector2d& Vector2d::zero()
{
    this->x = 0;
    this->y = 0;

    return *this;
}

Vector2d& Vector2d::normalize()
{
    float magnitude = sqrtf(this->x * this->x + this->y * this->y);
    if (magnitude != 0) {
        this->x /= magnitude;
        this->y /= magnitude;
    }

    return *this;
}
