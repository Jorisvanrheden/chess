#pragma once

#include "Board.h"
#include <tuple>
#include <math.h>

class MoveSet
{
public:
    MoveSet(std::vector<std::tuple<Coordinate, Coordinate>>& moves);

    bool move(Board& board);

    int getMoveCount() 
    {
        return moves.size();
    }

    Coordinate getMoveDiff(int moveIndex) 
    {
        if (moveIndex >= moves.size()) return Coordinate(0, 0);

        int diffX = abs(std::get<1>(moves[moveIndex]).getX() - std::get<0>(moves[moveIndex]).getX());
        int diffY = abs(std::get<1>(moves[moveIndex]).getY() - std::get<0>(moves[moveIndex]).getY());

        return Coordinate(diffX, diffY);
    }

    Coordinate getStart(int moveIndex)
    {
        if (moveIndex >= moves.size()) return Coordinate(0, 0);

        return std::get<0>(moves[moveIndex]);
    }

    Coordinate getTarget(int moveIndex) 
    {
        if (moveIndex >= moves.size()) return Coordinate(0, 0);
    
        return std::get<1>(moves[moveIndex]);
    }

private:
    std::vector<std::tuple<Coordinate, Coordinate>> moves;
};