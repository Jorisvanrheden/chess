#pragma once

#include "Piece.h"
#include "Coordinate.h"
#include "Board.h"

class IMoveValidator 
{
public:
	virtual bool isMoveValid(const Board& board, Piece* piece, const Coordinate& coordinate) = 0;
};