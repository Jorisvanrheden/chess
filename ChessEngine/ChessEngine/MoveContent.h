#pragma once

#include "Piece.h"
#include "Board.h"

class MoveContent
{
public:
    MoveContent(Piece* activePiece, Coordinate from, Coordinate to, std::vector<Piece*> targets)
        : activePiece(activePiece), from(from), to(to), targets(targets)
    {

    };
    ~MoveContent() {};

    Piece* activePiece;

    Coordinate from;
    Coordinate to;

    std::vector<Piece*> targets;
private:
    
};