#pragma once

#include "Board.h"

class IBoardPopulator 
{
public:
	virtual void populate(Board& board) = 0;
};