#include "Mouse.h"

static Direction moveDirection(Posicion &move);

/**
 * @brief Make move if possible.
 * 
 * @param maze The maze.
 * @param move The move to make.
 * @return Move is possible and done.
*/
bool makeMove(Tablero &tablero, Posicion move)
{
    Square newPosition = {tablero.position.x + move.x, tablero.position.y + move.y};
    bool found = false;
    auto vecinos = tablero.board[tablero.position.x][tablero.position.y].vecinos;
    for (Posicion position : virtual)
    {
        if (newPosition.x == position.x && newPosition.y == position.y)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        return false;
    }
    Direction moveDir = moveDirection(move);
    while (tablero.direction != moveDir)
    {
        API::turnRight();
    }
    API::moveForward();
    tablero.position = newPosition;
    return true;
}

/**
 * @brief Update graph edges based on walls around mouse.
 * 
 * @param maze The maze.
*/
void updateGraph(Tablero &tablero)
{
    auto currentNode = maze.board[tablero.position.x][tablero.position.y];
    bool fWall = API::wallFront();
    bool rWall = API::wallRight();
    bool lWall = API::wallLeft();
    std::vector<Square>::iterator iter;
    for (iter = currentNode.neighbors.begin(); iter != currentNode.neighbors.end(); iter++)
    {
        Square move = {iter->x - maze.position.x, iter->y - maze.position.y};
        Direction moveDir = moveDirection(move);
        /**
         * @todo Eliminate invalid connections.
        */
    }
}

/**
 * @brief Determine the direction of a move.
 * 
 * @param move The move.
 * @return The direction of the move.
*/
static Direction moveDirection(Posicion &move)
{
    if (move.y == 1)
        return UP;
    else if (move.y == -1)
        return DOWN;
    else if (move.x == 1)
        return RIGHT;
    else
        return LEFT;
}