#pragma once

#include "Board.h"

class IMoveSet 
{
public:
	virtual bool move(Board& board) = 0;
};