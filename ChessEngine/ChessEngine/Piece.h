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

	virtual int getID() = 0;
	virtual std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board) = 0;

	bool isSameType(Piece* piece) 
	{
		return piece->type == type;
	}

	bool isSameType(PlayerType type)
	{
		return this->type == type;
	}

	void addCoordinateToHistory(const Coordinate& coordinate) 
	{
		coordinateHistory.push_back(coordinate);
	}

protected:
	PlayerType type;
	std::vector<Coordinate> coordinateHistory;

	void getDirectionalUnits(std::vector<Coordinate>& moves, const Board& board, Coordinate coordinate, const Direction& direction, int limit, int iteration = 0);
	void getDirectionalMoves(std::vector<Coordinate>& moves, const Board& board, Coordinate coordinate, const Direction& direction, int limit = -1, int iteration = 0);
};