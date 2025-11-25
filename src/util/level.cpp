#include "components/collision.h"
#include "components/transform.h"
#include "components/sprite.h"

#include "level.h"
#include "global.h"

Level::Level(int width, int height)
{
    generateTiles(width, height);
    placeTiles();
}

/** Generate noise map with tiles */
void Level::generateTiles(int width, int height)
{
    int octaves = 5;
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

            auto tile = TilePlacement{
                .x = x * mapScale,
                .y = y * mapScale,
            };

            // for local variants
            auto local = rand() % (100 + 1);

            if (tileValue < 0.1) {
                tile.typeId = SNOW;
            }
            else if (tileValue < 0.27) {
                tile.typeId = ROCK;
            }
            else if (tileValue < 0.55) {
                tile.typeId = local < 5 ? TREE : GRASS;
            }
            else if (tileValue < 0.60) {
                tile.typeId = SAND;
            }
            else {
                tile.typeId = WATER;
            }

            tiles.push_back(tile);
        }
    }
}

/** Place maps in world */
void Level::placeTiles()
{
    for (auto t : tiles) {

        // int spriteRows = 3;
        // srcRect.x = (tileId % spriteRows) * w;
        // srcRect.y = (tileId / spriteRows) * h;
        SDL_Rect src{
            .x = t.typeId * 32,
            .y = 0,
            .h = 32,
            .w = 32,
        };

        auto tile = global.ecs->createEntity();
        global.ecs->addComponent(tile, Transform{.position = Vector2d(t.x, t.y)});
        global.ecs->addComponent(tile, Sprite{
                                           .filepath = "assets/terrain.png",
                                           .src = src,
                                       });

        switch (t.typeId) {
        case ROCK:
            // case WATER:
            global.ecs->addComponent(tile, Collision{});
            break;

        default:
            break;
        }

        // add treasure to tile
        auto hasTreasure = (rand() % (100 + 1) < 1);
        if (!hasTreasure) {
            continue;
        }

        int treasureId = -1;

        switch (t.typeId) {
        case WATER:
        case SAND:
            treasureId = SEASHELL;
            break;

        case GRASS:
            break;

        case SNOW:
            break;

        default:
        case ROCK:
        case TREE:
            break;
        }

        if (treasureId == -1) {
            continue;
        }

        auto treasureTile = global.ecs->createEntity();
        global.ecs->addComponent(treasureTile, Transform{.position = Vector2d(t.x, t.y)});
        global.ecs->addComponent(treasureTile, Collision{.collectible = true});
        global.ecs->addComponent(
            treasureTile, Sprite{
                              .filepath = "assets/treasures.png",
                              .src = {
                                  .x = treasureId * 32,
                                  .y = 0,
                                  .h = 32,
                                  .w = 32,
                              },
                          });
    }
}

TilePlacement Level::getFreeTile(int startX, int startY)
{
    for (auto t : tiles) {

        if (t.x < startX || t.y < startY) {
            continue;
        }

        switch (t.typeId) {
        case ROCK:
            //    case WATER:
        case TREE:
            break;

            // first free tile
        default:
            return t;
        }
    }

    return tiles.at(tiles.size() / 2);
}