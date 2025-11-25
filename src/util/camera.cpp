#include "camera.h"

Camera::Camera(int width, int height)
{
    windowSize = {0, 0, width, height};
    position = {0, 0, width, height};
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