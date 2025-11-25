#include "camera.h"

void Camera::setPosition(int w, int h)
{
    windowSize = {0, 0, w, h};
    position = {0, 0, w, h};
}

void Camera::update(Vector2d playerPosition)
{
    position.x = playerPosition.x - windowSize.w / 2;
    position.y = playerPosition.y - windowSize.h / 2;

    // check bounds
    if (position.x < 0) {
        position.x = 0;
    }
    if (position.y < 0) {
        position.y = 0;
    }
    if (position.x > position.w) {
        position.x = position.w;
    }
    if (position.y > position.h) {
        position.y = position.h;
    }
}