#pragma once

#include "Coordinate.h"
#include "Board.h"

class IMoveHandler 
{
public:
	virtual MoveSet* getMoveSet(Board& board, const Coordinate& origin, const Coordinate& target) = 0;
};