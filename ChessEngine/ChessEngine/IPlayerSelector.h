#pragma once

#include <vector>
#include "Coordinate.h"
#include "IMoveSet.h"

class IPlayerSelector 
{
public:
	virtual bool canMove(const Board& board, const Coordinate& coordinate) = 0;
	virtual PLAYER_TYPE getActivePlayer() = 0;
	virtual void nextPlayer() = 0;
	virtual int getPlayerCount() = 0;
};