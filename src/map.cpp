#include "map.h"
#include "game.h"

/** Generate noise map with tiles */
void Map::generate(int width, int height)
{
    float* seed = new float[width * height];
    for (int i = 0; i < width * height; i++) {
        seed[i] = (float)rand() / (float)RAND_MAX;
    }

    float bias = 2.0f;
    int octaves = 5;
    int mapScale = 32;

    width /= mapScale;
    height /= mapScale;

    float* perlinNoise = new float[width * height];

    // generate noise
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float noise = 0.0f;
            float scale = 1.0f;
            float scaleAccumulated = 0.0f;

            for (int o = 0; o < octaves; o++) {
                int pitch = width >> o;
                int sampleX1 = (x / pitch) * pitch;
                int sampleY1 = (y / pitch) * pitch;

                int sampleX2 = (sampleX1 + pitch) % width;
                int sampleY2 = (sampleY1 + pitch) % width;

                float fBlendX = (float)(x - sampleX1) / (float)pitch;
                float blendY = (float)(y - sampleY1) / (float)pitch;

                float sampleT = (1.0f - fBlendX) * seed[sampleY1 * width + sampleX1] + fBlendX * seed[sampleY1 * width + sampleX2];
                float sampleB = (1.0f - fBlendX) * seed[sampleY2 * width + sampleX1] + fBlendX * seed[sampleY2 * width + sampleX2];

                scaleAccumulated += scale;
                noise += (blendY * (sampleB - sampleT) + sampleT) * scale;
                scale = scale / bias;
            }

            // Scale to seed range
            perlinNoise[y * width + x] = noise / scaleAccumulated;
        }
    }

    // map to tiles
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float tileValue = perlinNoise[y * width + x] * 3.0f;

            if (tileValue < 0.35) {
                Game::addTile(0, x * mapScale, y * mapScale);
            }
            else if (tileValue >= 0.35 && tileValue < 0.6) {
                Game::addTile(1, x * mapScale, y * mapScale);
            }
            else {
                Game::addTile(2, x * mapScale, y * mapScale);
            }
        }
    }
}
