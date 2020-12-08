#pragma once

#include "Piece.h"
#include "Board.h"

class IBoardAnalyzer 
{
public:
	virtual int analyzeStatus(Board& board, PLAYER_TYPE player) = 0;
};