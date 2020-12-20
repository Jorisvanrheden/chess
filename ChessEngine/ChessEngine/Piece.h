#pragma once

#include <vector>
#include "Coordinate.h"
#include "Direction.h"
#include "GameConstants.h"

class ISpecialMove;
class Board;
class IMoveSet;

class Piece
{
public:
	Piece(const PLAYER_TYPE& type);

	virtual PIECE_TYPE getID() = 0;
	virtual std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board) = 0;

	bool isSameType(Piece* piece)
	{
		return piece->type == type;
	}

	bool isSameType(PLAYER_TYPE type)
	{
		return this->type == type;
	}

	void addCoordinateToHistory(const Coordinate& coordinate)
	{
		coordinateHistory.push_back(coordinate);
	}

	void removeLastCoordinate()
	{
		if (coordinateHistory.size() > 0) 
		{
			coordinateHistory.pop_back();
		}
	}
	
	Coordinate getCurrentCoordinate() const
	{
		return coordinateHistory[coordinateHistory.size() - 1];
	}

	int getMoveCount() const 
	{
		return coordinateHistory.size();
	}

	PLAYER_TYPE getPlayerType() const
	{
		return type;
	}

	void addSpecialMove(ISpecialMove* specialMove) 
	{
		specialMoves.push_back(specialMove);
	}

	std::vector<ISpecialMove*> specialMoves;

protected:
	PLAYER_TYPE type;
	std::vector<Coordinate> coordinateHistory;


	void addTest(const Board& board, std::vector<Coordinate>& moves);
	void getMovesInDirection(std::vector<Coordinate>& moves, const Board& board, Coordinate coordinate, const Direction& direction, int limit = -1, bool includeHit = true);
};