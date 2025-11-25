#pragma once

class Vector2d {
public:
    float x, y;

    Vector2d();
    Vector2d(float x, float y);

    Vector2d& add(const Vector2d& vec);
    Vector2d& subtract(const Vector2d& vec);
    Vector2d& multiply(const Vector2d& vec);
    Vector2d& divide(const Vector2d& vec);

    friend Vector2d& operator+(Vector2d& v1, const Vector2d& v2);
    friend Vector2d& operator-(Vector2d& v1, const Vector2d& v2);
    friend Vector2d& operator*(Vector2d& v1, const Vector2d& v2);
    friend Vector2d& operator/(Vector2d& v1, const Vector2d& v2);

    Vector2d& operator+=(const Vector2d vec);
    Vector2d& operator-=(const Vector2d vec);
    Vector2d& operator*=(const Vector2d vec);
    Vector2d& operator/=(const Vector2d vec);
};