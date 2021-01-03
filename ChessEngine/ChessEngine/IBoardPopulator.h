#pragma once

#include "Board.h"

class IBoardPopulator 
{
public:
	virtual void populate(Board& board) = 0;

	virtual int getWidth() = 0;
	virtual int getHeight() = 0; 
};