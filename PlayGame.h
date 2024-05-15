/**
 *
 */
#pragma once
#include <vector>
#include "API.h"

struct Posicion
{
    int x, y;
};

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct GraphNode
{
    int distance;
    bool visitado;
    std::vector<Posicion> vecinos;
};

struct Laberinto
{
    GraphNode **tablero;
    Direction direction;
    Posicion position;
    int width;
    int height;
};

Laberinto initMaze();
void updateDistances(Laberinto &tablero);