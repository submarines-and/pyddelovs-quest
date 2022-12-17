#include "level.h"
#include "components/tile-component.h"
#include "components/collision-component.h"
#include "global.h"

/** Generate noise map with tiles */
std::vector<TilePlacement> Level::generateTiles(int width, int height)
{
    int octaves = 6;
    int mapScale = 32;

    width /= mapScale;
    height /= mapScale;

    srand((unsigned int)time(NULL));

    float* seed = new float[width * height * 34354 * 11633];
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

    std::vector<TilePlacement> tiles;

    // map to tiles
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float tileValue = perlinNoise[y * width + x];

            TilePlacement tile = TilePlacement();
            tile.x = x * mapScale;
            tile.y = y * mapScale;

            if (tileValue < 0.1) {
                tile.typeId = TileComponent::SNOW;
            }
            else if (tileValue < 0.27) {
                tile.typeId = TileComponent::ROCK;
            }
            else if (tileValue < 0.56) {
                tile.typeId = TileComponent::GRASS;
            }
            else if (tileValue < 0.58) {
                tile.typeId = TileComponent::FLOWER;
            }
            else if (tileValue < 0.6) {
                tile.typeId = TileComponent::TREE;
            }
            else if (tileValue < 0.7) {
                tile.typeId = TileComponent::SAND;
            }
            else {
                tile.typeId = TileComponent::WATER;
            }

            tiles.push_back(tile);
        }
    }

    return tiles;
}

/** Place maps in world */
void Level::placeTiles(std::vector<TilePlacement> tiles)
{
    for (auto t : tiles) {

        auto& tile(global.entityManager.addEntity());
        tile.addComponent<TileComponent>(t.x, t.y, 32, 32, t.typeId);

        switch (t.typeId) {
        case TileComponent::ROCK:
        case TileComponent::WATER:
            tile.addComponent<CollisionComponent>();
            break;

        default:
            break;
        }
    }
}

void Level::generate(int width, int height)
{
    auto tiles = generateTiles(width, height);
    placeTiles(tiles);
}