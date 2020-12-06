#pragma once

#include "Piece.h"
#include "Coordinate.h"
#include "Board.h"

class IMoveValidator 
{
public:
	virtual bool isMoveValid(const Board& board, Piece* piece, const Coordinate& origin, const Coordinate& target) = 0;
};