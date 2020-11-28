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

	bool IsSameType(Piece* piece) 
	{
		return piece->type == type;
	}

private:
	PlayerType type;
};