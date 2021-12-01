#pragma once

#include <vector>
#include "Coordinate.h"
#include "Direction.h"
#include "GameConstants.h"

class Board;
class MoveSet;

class Piece
{
public:
	Piece(const PLAYER_TYPE& type);

	virtual PIECE_TYPE getID() = 0;

	virtual std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board) = 0;
    virtual std::vector<Coordinate> findAdditionalMoves(const Coordinate& coordinate, const Board& board) 
    {
        return std::vector<Coordinate>();
    }
    virtual std::vector<MoveSet*> transformMoves(const std::vector<Coordinate>& moves, const Board& board);
    virtual MoveSet* getMoveSet(const Coordinate& target, const Board& board);

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

protected:
	PLAYER_TYPE type;
	std::vector<Coordinate> coordinateHistory;

	void getMovesInDirection(std::vector<Coordinate>& moves, const Board& board, Coordinate coordinate, const Direction& direction, int limit = -1, bool includeHit = true);
};