#include "map.h"
#include "ecs/tile-component.h"

/** Will be populated by the generate function*/
std::vector<TilePlacement> Map::tiles;

/** Generate noise map with tiles */
void Map::generate(int width, int height)
{
    int octaves = 4;
    int mapScale = 32;

    width /= mapScale;
    height /= mapScale;

    srand((unsigned int)time(NULL));
    float* seed = new float[width * height];
    for (int i = 0; i < width * height; i++) {
        seed[i] = (float)rand() / (float)RAND_MAX;
    }

    float* perlinNoise = new float[width * height];

    // generate noise
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float noise = 0.0f;
            float scale = 0.5f;
            float scaleAccumulated = 0.0f;

            for (int o = 0; o < octaves; o++) {
                int pitch = width >> o;
                int sampleX1 = (x / pitch) * pitch;
                int sampleY1 = (y / pitch) * pitch;

                int sampleX2 = (sampleX1 + pitch) % width;
                int sampleY2 = (sampleY1 + pitch) % width;

                float blendX = (float)(x - sampleX1) / (float)pitch;
                float blendY = (float)(y - sampleY1) / (float)pitch;

                float sampleT = (1.0f - blendX) * seed[sampleY1 * width + sampleX1] + blendX * seed[sampleY1 * width + sampleX2];
                float sampleB = (1.0f - blendX) * seed[sampleY2 * width + sampleX1] + blendX * seed[sampleY2 * width + sampleX2];

                scaleAccumulated += scale;
                noise += (blendY * (sampleB - sampleT) + sampleT) * scale;
            }

            // Scale to seed range
            perlinNoise[y * width + x] = noise / scaleAccumulated;
        }
    }

    // map to tiles
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float tileValue = perlinNoise[y * width + x];

            TilePlacement tile = TilePlacement();
            tile.x = x * mapScale;
            tile.y = y * mapScale;

            if (tileValue < 0.32) {
                tile.typeId = TileComponent::ROCK;
            }
            else if (tileValue < 0.6) {
                tile.typeId = TileComponent::GRASS;
            }
            else if (tileValue < 0.65) {
                tile.typeId = TileComponent::SAND;
            }
            else {
                tile.typeId = TileComponent::WATER;
            }

            tiles.push_back(tile);
        }
    }
}
