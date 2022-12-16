#include "quad-tree.h"
#include <SDL2/SDL.h>

QuadTree::QuadTree() : left(0), right(0), top(0), down(0), numObjectsToGrow(4), nodes(0), isLeaf(true) {}

QuadTree::QuadTree(double _left, double _right, double _top, double _down, unsigned int _numObjectsToGrow) : left(_left), right(_right), top(_top), down(_down), numObjectsToGrow(_numObjectsToGrow), nodes(0), isLeaf(true) {}

QuadTree::~QuadTree()
{
    if (!isLeaf)
        delete[] nodes;
}

void QuadTree::addObject(SDL_Rect* object)
{
    if (isLeaf) {
        objects.push_back(object);
        bool reachedMaxObjects = (objects.size() == numObjectsToGrow);
        if (reachedMaxObjects) {
            createLeaves();
            moveObjectsToLeaves();
            isLeaf = false;
        }
        return;
    }

    for (int n = 0; n < NodeCount; ++n) {
        if (nodes[n].contains(object)) {
            nodes[n].addObject(object);
            return;
        }
    }

    objects.push_back(object);
}

void QuadTree::clear()
{
    objects.clear();

    if (!isLeaf) {
        for (int n = 0; n < NodeCount; ++n) {
            nodes[n].clear();
        }
    }
}

std::vector<SDL_Rect*> QuadTree::getObjectsAt(double x, double y)
{
    if (isLeaf) {
        return objects;
    }

    std::vector<SDL_Rect*> returnedObjects;
    std::vector<SDL_Rect*> childObjects;

    if (!objects.empty())
        returnedObjects.insert(returnedObjects.end(), objects.begin(), objects.end());

    for (int n = 0; n < NodeCount; ++n) {
        if (nodes[n].contains(x, y)) {
            childObjects = nodes[n].getObjectsAt(x, y);
            returnedObjects.insert(returnedObjects.end(), childObjects.begin(), childObjects.end());
            break;
        }
    }

    return returnedObjects;
}

void QuadTree::display(SDL_Renderer* renderer)
{
    SDL_Rect rect;
    rect.x = left;
    rect.y = top;
    rect.w = right - left;
    rect.h = down - top;
    SDL_RenderDrawRect(renderer, &rect);

    if (!isLeaf) {
        for (int n = 0; n < NodeCount; ++n) {
            nodes[n].display(renderer);
        }
    }
}

bool QuadTree::contains(SDL_Rect* object)
{
    return object->x > left &&
           (object->x + object->w) < right &&
           object->y > top &&
           (object->y + object->h) < down;
}

bool QuadTree::contains(double x, double y)
{
    return (x >= left && x <= right) &&
           (y >= top && y <= down);
}

void QuadTree::createLeaves()
{
    nodes = new QuadTree[4];
    nodes[NW] = QuadTree(left, (left + right) / 2, top, (top + down) / 2, numObjectsToGrow);
    nodes[NE] = QuadTree((left + right) / 2, right, top, (top + down) / 2, numObjectsToGrow);
    nodes[SW] = QuadTree(left, (left + right) / 2, (top + down) / 2, down, numObjectsToGrow);
    nodes[SE] = QuadTree((left + right) / 2, right, (top + down) / 2, down, numObjectsToGrow);
}

void QuadTree::moveObjectsToLeaves()
{
    for (int n = 0; n < NodeCount; ++n) {
        for (unsigned int m = 0; m < objects.size(); ++m) {
            if (nodes[n].contains(objects[m])) {
                nodes[n].addObject(objects[m]);
                objects.erase(objects.begin() + m);
                --m;
            }
        }
    }
}