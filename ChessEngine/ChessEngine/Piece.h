#pragma once

#include <vector>
#include "Coordinate.h"
#include "Direction.h"
#include "GameFlags.h"

class Board;

class Piece 
{
public:
	Piece(const PlayerType& type);

	virtual std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board) = 0;

	bool isSameType(Piece* piece) 
	{
		return piece->type == type;
	}

protected:
	PlayerType type;

	void getDirectionalMoves(std::vector<Coordinate>& moves, const Board& board, Coordinate coordinate, const Direction& direction, int limit = -1, int iteration = 0);
};