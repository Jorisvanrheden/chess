#pragma once

#include "Coordinate.h"
#include "Board.h"

class IMoveHandler 
{
public:
	virtual void movePiece(Board& board, Piece* piece, const Coordinate& origin, const Coordinate& target) = 0;
};