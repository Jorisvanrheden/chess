#pragma once

#include "Board.h"
#include <tuple>
#include <math.h>

#include "MoveContent.h"

class MoveSet
{
public:
    MoveSet(const std::vector<MoveContent>& moves);

    bool move(Board& board);

    int getMoveCount() 
    {
        return moves.size();
    }

    Coordinate getMoveDiff(int moveIndex) 
    {
        if (moveIndex >= moves.size()) return Coordinate(0, 0);

        int diffX = abs(moves[moveIndex].to.getX() - moves[moveIndex].from.getX());
        int diffY = abs(moves[moveIndex].to.getY() - moves[moveIndex].from.getY());

        return Coordinate(diffX, diffY);
    }

    Coordinate getStart(int moveIndex)
    {
        if (moveIndex >= moves.size()) return Coordinate(0, 0);

        return moves[moveIndex].from;
    }

    Coordinate getTarget(int moveIndex) 
    {
        if (moveIndex >= moves.size()) return Coordinate(0, 0);
    
        return moves[moveIndex].to;
    }

    MoveContent getContent(int index) 
    {
        return moves[index];
    }

    void setContent(int index, const std::vector<Piece*>& targets) 
    {
        moves[index].targets = targets;
    }

private:
    std::vector<MoveContent> moves;
};