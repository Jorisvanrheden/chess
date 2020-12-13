#pragma once

#include "IMoveSet.h"
#include "Coordinate.h"

class MoveSetSingle : public IMoveSet
{
public:
	MoveSetSingle(const Coordinate& from, const Coordinate& to) : from(from), to(to)
	{
	
	}

	bool move(Board& board)
	{
		return board.movePiece(from, to);
	}

private:
	Coordinate from;
	Coordinate to;
};