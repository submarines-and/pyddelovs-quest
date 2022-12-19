#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "components/collision.h"
#include "components/transform.h"
#include "components/sprite.h"

#include "level.h"
#include "global.h"

Level::Level(int width, int height)
{
    generateTiles(width, height);
    placeTiles(width, height);
    placeObjects();
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

            if (tileValue < 0.3) {
                tile.typeId = SNOW;
            }
            else if (tileValue < 0.55) {
                tile.typeId = GRASS;
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
void Level::placeTiles(int width, int height)
{
    auto* surface = IMG_Load("assets/terrain.png");
    auto* terrainTexture = SDL_CreateTextureFromSurface(global.renderer, surface);
    SDL_FreeSurface(surface);

    auto* levelTexture = SDL_CreateTexture(global.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetRenderTarget(global.renderer, levelTexture);
    SDL_RenderClear(global.renderer);

    for (auto t : tiles) {
        SDL_Rect src{
            .x = t.typeId * 32,
            .y = 0,
            .h = 32,
            .w = 32,
        };

        SDL_Rect dest{
            .w = 32,
            .h = 32,
            .x = t.x,
            .y = t.y,
        };

        SDL_RenderCopy(global.renderer, terrainTexture, &src, &dest);
    }
    SDL_SetRenderTarget(global.renderer, NULL);

    auto level = global.ecs->createEntity();
    global.ecs->addComponent(level, Transform{
                                        .position = Vector2d(0, 0),
                                        .width = width,
                                        .height = height,
                                    });
    global.ecs->addComponent(level, Sprite{.texture = levelTexture, .src = {.x = 0, .y = 0, .w = width, .h = height}});
}

void Level::placeObjects()
{
    for (auto t : tiles) {

        // add treasure to tile
        auto hasObstacle = (rand() % (100 + 1) < 1);
        auto hasTreasure = !hasObstacle && (rand() % (100 + 1) < 1);
        if (!hasTreasure && !hasObstacle) {
            continue;
        }

        int treasureId = -1;
        int obstacleId = -1;

        switch (t.typeId) {
        case WATER:
        case SAND:
            treasureId = SEASHELL;
            obstacleId = ROCK;
            break;

        case GRASS:
            treasureId = FLOWER;
            obstacleId = TREE;
            break;

        case SNOW:
            treasureId = BREAD;
            obstacleId = TREE;
            break;

        default:
            break;
        }


        auto treasureTile = global.ecs->createEntity();
        global.ecs->addComponent(treasureTile, Transform{.position = Vector2d(t.x, t.y)});
        global.ecs->addComponent(treasureTile, Collision{.treasureId = hasTreasure ? treasureId : -1});

        global.ecs->addComponent(
            treasureTile, Sprite{
                              .filepath = hasTreasure ? "assets/treasures.png" : "assets/obstacles.png",
                              .src = {
                                  .x = (hasTreasure ? treasureId : obstacleId) * 32,
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
    }

    return tiles.at(tiles.size() / 2);
}