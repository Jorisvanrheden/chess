#pragma once

#include "IMoveSet.h"

class ISpecialMove 
{
public:
	virtual IMoveSet* getMove(const std::string& moveString, PLAYER_TYPE type) = 0;
	virtual IMoveSet* getMove(const Coordinate& target, PLAYER_TYPE type) = 0;
	virtual bool isPartOfSpecialMove(const Coordinate& target) = 0;

	virtual std::vector<Coordinate> getInitiatingMoves(const Board& board) = 0;
};