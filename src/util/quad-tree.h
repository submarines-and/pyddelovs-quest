#pragma once
#include <vector>
#include "SDL2/SDL.h"

class QuadTree {
    enum Node {
        NW = 0,
        NE,
        SW,
        SE,
        NodeCount
    };

public:
    QuadTree();
    QuadTree(double left, double right, double top, double down, unsigned int numObjectsToGrow = 3);
    ~QuadTree();

    void addObject(SDL_Rect* object);
    void clear();
    std::vector<SDL_Rect*> getObjectsAt(double x, double y);
    void display(SDL_Renderer* renderer);

private:
    double left;
    double right;
    double top;
    double down;
    unsigned int numObjectsToGrow;
    std::vector<SDL_Rect*> objects;
    QuadTree* nodes;
    bool isLeaf;
    bool contains(SDL_Rect* object);
    bool contains(double x, double y);
    void createLeaves();
    void moveObjectsToLeaves();
};