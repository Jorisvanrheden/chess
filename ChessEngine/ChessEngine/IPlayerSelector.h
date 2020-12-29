#pragma once

#include <vector>
#include "Coordinate.h"
#include "IMoveSet.h"

class IPlayerSelector 
{
public:
	virtual void moveSet(IMoveSet* set) = 0;
	virtual bool canMove(const Coordinate& coordinate) = 0;
	//virtual void movePiece(const Coordinate& origin, const Coordinate& target) = 0;
	virtual PLAYER_TYPE getActivePlayer() = 0;
};