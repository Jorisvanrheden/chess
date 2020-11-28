#pragma once

#include <vector>
#include "Coordinate.h"
#include "GameFlags.h"

class Board;

class Piece 
{
public:
	Piece(const PlayerType& type) 
		: type(type)
	{
	}

	virtual std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board) = 0;

	bool isSameType(Piece* piece) 
	{
		return piece->type == type;
	}

protected:
	PlayerType type;
};