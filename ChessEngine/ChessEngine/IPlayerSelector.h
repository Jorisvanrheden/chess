#pragma once

#include <vector>
#include "Coordinate.h"

class IPlayerSelector 
{
public:
	virtual void movePiece(const Coordinate& origin, const Coordinate& target) = 0;
	virtual std::vector<Coordinate> getAvailableMoves(const Coordinate& coordinate) = 0;
};