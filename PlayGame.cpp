/**
 *  Functions related to solving the maze
 */
#include "API.h"
#include "Maze.h"

#include <iterator>

static void Play(Laberinto &tablero, Posicion &posicionaActual);

/**
 * @brief Create new maze.
 * 
 * @return The new maze.
*/
Laberinto initMaze()
{
    
    Laberinto tablero;
    tablero.width = API::mazeWidth();
    tablero.height = API::mazeHeight();
    // Initialize a maze with all squares connected (no walls).
    tablero.tablero = (GraphNode **)malloc(tablero.width * sizeof(GraphNode *));
    for (int i = 0; i < tablero.width; i++)
    {
        tablero.tablero[i] = (GraphNode *)malloc(tablero.height * sizeof(GraphNode));
    }
    for (int i = 0; i < tablero.width; i++)
    {
        for (int j = 0; j < tablero.height; j++)
        {
            if (i > 0)
                tablero.tablero[i][j].vecinos.push_back({i - 1, j});
            if (i < tablero.width - 1)
                tablero.tablero[i][j].vecinos.push_back({i + 1, j});
            if (j > 0)
                tablero.tablero[i][j].vecinos.push_back({i, j - 1});
            if (j < tablero.height - 1)
                tablero.tablero[i][j].vecinos.push_back({i, j + 1});
            tablero.tablero[i][j].visitado = false;
        }
    }
    tablero.position = {0, 0};
    tablero.direction = UP;
    return tablero;
}

/**
 * @brief Update distances based on existing graph edges.
 * 
 * @param maze The maze.
*/
void updateDistances(Laberinto &tablero)
{
    for (int i = 0; i < tablero.width; i++)
    {
        for (int j = 0; j < tablero.height; j++)
        {
            tablero.tablero[i][j].distance = 100;
            tablero.tablero[i][j].visitado = false;
        }
    }
    Posicion targetSquare = {tablero.width / 2, tablero.height / 2};
    tablero.tablero[targetSquare.x][targetSquare.y].distance = 0;
    tablero.tablero[targetSquare.x - 1][targetSquare.y].distance = 0;
    tablero.tablero[targetSquare.x][targetSquare.y - 1].distance = 0;
    tablero.tablero[targetSquare.x - 1][targetSquare.y - 1].distance = 0;
    (tablero, targetSquare);
    for (int i = 0; i < maze.width; i++)
    {
        for (int j = 0; j < maze.height; j++)
        {
            API::setText(i, j, std::to_string(maze.board[i][j].distance));
        }
    }
}

/**
 * @brief Internal function implementing Dijkstra's algorithm to assign distances to nodes.
 * 
 * @param maze The maze.
 * @param currentSquare The square being visited.
*/
static void Play(Laberinto &tablero, Posicion &currentSquare)
{
    auto currentNode = &tablero.tablero[currentSquare.x][currentSquare.y];
    if (currentNode->visitado)
        return;
    currentNode->visitado = true;

    for (Posicion &visitSquare : currentNode->vecinos)
    {
        auto visitNode = &tablero.tablero[visitSquare.x][visitSquare.y];
        if (visitNode->visitado)
            continue;
        visitNode->distance = std::min(currentNode->distance + 1, visitNode->distance);
    }
    for (Posicion &visitSquare : currentNode->vecinos)
        Play(tablero, visitSquare);
}